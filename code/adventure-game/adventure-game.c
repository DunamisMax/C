#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

// Original map layout
static const char *map_data[] = {
    "###########",
    "#.........#",
    "#....@....#",
    "#....$....#",
    "###########"
};

#define MAP_HEIGHT (sizeof(map_data)/sizeof(map_data[0]))
#define MAP_WIDTH  (11)

// We'll copy the map to a mutable array so we can remove '@' after reading.
static char game_map[MAP_HEIGHT][MAP_WIDTH];

// Player coordinates
static int player_y = 0;
static int player_x = 0;

// Find player start position '@' in game_map
static void find_player_start(void) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (game_map[y][x] == '@') {
                player_y = y;
                player_x = x;
                // Replace '@' with '.' because now it's just floor under the player
                game_map[y][x] = '.';
                return;
            }
        }
    }
}

// Check if a cell is walkable (not a wall)
static int can_walk(int y, int x) {
    // Boundary check
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH) {
        return 0;
    }
    char c = game_map[y][x];
    return (c == '.' || c == '$');
}

// Draw the map and the player
static void draw_map(void) {
    clear();

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            char ch = game_map[y][x];

            if (y == player_y && x == player_x) {
                // Draw the player '@'
                attron(COLOR_PAIR(2));
                mvaddch(y, x, '@');
                attroff(COLOR_PAIR(2));
            } else {
                // Draw the map character
                if (ch == '#') {
                    attron(COLOR_PAIR(1)); // Walls in a different color
                    mvaddch(y, x, ch);
                    attroff(COLOR_PAIR(1));
                } else if (ch == '$') {
                    attron(COLOR_PAIR(3)); // Treasure highlighted
                    mvaddch(y, x, ch);
                    attroff(COLOR_PAIR(3));
                } else {
                    mvaddch(y, x, ch);
                }
            }
        }
    }

    mvprintw(MAP_HEIGHT, 0, "Use arrow keys or WASD to move. Press 'q' to quit.");
    refresh();
}

int main(void) {
    // Copy map_data into a mutable array
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            game_map[y][x] = map_data[y][x];
        }
    }

    // Initialize ncurses
    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return EXIT_FAILURE;
    }

    // Set up ncurses modes
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Check if terminal supports colors
    if (has_colors()) {
        start_color();
        // Initialize some color pairs
        // COLOR_PAIR(1) for walls, COLOR_PAIR(2) for player, COLOR_PAIR(3) for treasure
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
    }

    // Find the player's start position
    find_player_start();

    // Initial title screen
    clear();
    mvprintw(0, 0, "Welcome to the Tiny Adventure!");
    mvprintw(1, 0, "Find the treasure '$' to win.");
    mvprintw(2, 0, "Press any key to start...");
    refresh();
    getch();

    // Game loop
    int running = 1;
    while (running) {
        draw_map();
        int ch = getch();

        int new_y = player_y;
        int new_x = player_x;

        if (ch == 'q' || ch == 'Q') {
            running = 0;
        } else if (ch == KEY_UP || ch == 'w') {
            new_y = player_y - 1;
        } else if (ch == KEY_DOWN || ch == 's') {
            new_y = player_y + 1;
        } else if (ch == KEY_LEFT || ch == 'a') {
            new_x = player_x - 1;
        } else if (ch == KEY_RIGHT || ch == 'd') {
            new_x = player_x + 1;
        }

        // Check if we can move there
        if (can_walk(new_y, new_x)) {
            player_y = new_y;
            player_x = new_x;

            // Check if stepped on treasure
            if (game_map[player_y][player_x] == '$') {
                clear();
                mvprintw(0, 0, "You found the treasure! Press any key to exit.");
                refresh();
                getch();
                running = 0;
            }
        }
    }

    // Exit screen
    clear();
    mvprintw(0, 0, "Thanks for playing!");
    mvprintw(1, 0, "Press any key to quit.");
    refresh();
    getch();

    // Clean up ncurses
    endwin();
    return EXIT_SUCCESS;
}
