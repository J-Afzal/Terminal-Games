# Main Menu Test Plan

## Initial Page

1. Run MainMenu via CLI constructor with no options set:

   Run MainMenu via constructor with `p_useAnsiEscapeCodes` set to `false`:

    ```text
    For Windows:

    ╔══════════════════════════════════════╗
    ║            Terminal Games            ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           Platform: Windows          ║
    ║                                      ║
    ║          Controls: Enhanced          ║
    ║                                      ║
    ║   Instructions: Use the arrows keys  ║
    ║    to navigate and press enter to    ║
    ║         confirm a selection.         ║
    ║                                      ║
    ║                                      ║
    ║ Use ANSI colour escape codes?        ║
    ║ > Yes                                ║
    ║   No                                 ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           q = quit program           ║
    ╚══════════════════════════════════════╝

    For macOS/Linux:

    ╔══════════════════════════════════════╗
    ║            Terminal Games            ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║       Platform: macOS or Linux       ║
    ║                                      ║
    ║          Controls: Enhanced          ║
    ║                                      ║
    ║    Instructions: Enter one of the    ║
    ║     WASD keys to navigate, 'e' to    ║
    ║   to confirm a selection and 'z' to  ║
    ║   undo a selection in Battleships.   ║
    ║                                      ║
    ║ Use ANSI colour escape codes?        ║
    ║ > Yes                                ║
    ║   No                                 ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           q = quit program           ║
    ╚══════════════════════════════════════╝
    ```

    > [!NOTE]
    > The output should be coloured.

1. When running via CLI constructor with `--a` or `--ascii-only`:

   Run MainMenu via constructor with `p_useAnsiEscapeCodes` set to `true`:

    ```text
    ╔══════════════════════════════════════╗
    ║            Terminal Games            ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           Platform: Windows          ║
    ║                                      ║
    ║          Controls: Enhanced          ║
    ║                                      ║
    ║   Instructions: Use the arrows keys  ║
    ║    to navigate and press enter to    ║
    ║         confirm a selection.         ║
    ║                                      ║
    ║                                      ║
    ║ Use ANSI colour escape codes?        ║
    ║   Yes                                ║
    ║ > No                                 ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           q = quit program           ║
    ╚══════════════════════════════════════╝

    For macOS/Linux:

    ╔══════════════════════════════════════╗
    ║            Terminal Games            ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║       Platform: macOS or Linux       ║
    ║                                      ║
    ║          Controls: Enhanced          ║
    ║                                      ║
    ║    Instructions: Enter one of the    ║
    ║     WASD keys to navigate, 'e' to    ║
    ║   to confirm a selection and 'z' to  ║
    ║   undo a selection in Battleships.   ║
    ║                                      ║
    ║ Use ANSI colour escape codes?        ║
    ║   Yes                                ║
    ║ > No                                 ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           q = quit program           ║
    ╚══════════════════════════════════════╝
    ```

    > [!NOTE]
    > The output should **not** be coloured.

## Toggling ANSI Colour Escape Codes

1. Starting from the homepage state with "Yes" selected (i.e. step 1 from [Initial Homepage Load](#initial-homepage-load)
   section) press `Enter` on Windows or enter "e" on macOS/Linux:

    ```text
    ╔══════════════════════════════╗
    ║           Main Menu          ║
    ╚══════════════════════════════╝
    ╔══════════════════════════════╗
    ║        > Tic Tac Toe         ║
    ║                              ║
    ║            Hangman           ║
    ║                              ║
    ║          Battleships         ║
    ╚══════════════════════════════╝
    ╔══════════════════════════════╗
    ║     q = quit to homepage     ║
    ╚══════════════════════════════╝
    ```

    > [!NOTE]
    > The output should be coloured.

1. Press `q` on Windows or enter "q" on macOS/Linux. Confirm the homepage is coloured with "Yes" selected.

1. Select "No" by pressing the down arrow key on Windows or entering "s" on macOS/Linux. Confirm the homepage is not coloured.

1. Press `Enter` on Windows or enter "e" on macOS/Linux. Confirm the output is the same as step 1 but without any colour.

1. Press `q` on Windows or enter "q" on macOS/Linux. Confirm the homepage is not coloured with "No" selected.

1. Select "Yes" by pressing the down arrow key on Windows or entering "s" on macOS/Linux. Confirm the homepage is coloured.

1. Select "No" by pressing the up arrow key on Windows or entering "w" on macOS/Linux. Confirm the homepage is not coloured.

## Main Menu Game Selection

1. Starting from homepage press `Enter` on Windows or enter "e" on macOS/Linux. Confirm the Tic Tac Toe game is selected.

1. Select Hangman by pressing the down arrow key on Windows or entering "s" on macOS/Linux.

1. Select Battleships by pressing the down arrow key on Windows or entering "s" on macOS/Linux.

1. Select Tic Tac Toe by pressing the down arrow key on Windows or entering "s" on macOS/Linux.

1. Select Battleships by pressing the up arrow key on Windows or entering "w" on macOS/Linux.

1. Press `q` on Windows or enter "q" on macOS/Linux. Press `Enter` on Windows or enter "e" on macOS/Linux. Confirm Tic Tac Toe
   is selected.

1. Press `Enter` on Windows or enter "e" on macOS/Linux. Confirm Tic Tac Toe game is launched.

1. Press `q` on Windows or enter "q" on macOS/Linux. Confirm Tic Tac Toe is selected. Select Hangman by pressing the down arrow
   key on Windows or entering "s" on macOS/Linux. Press `Enter` on Windows or enter "e" on macOS/Linux. Confirm Hangman game is
   launched.

1. Press `q` on Windows or enter "q" on macOS/Linux. Confirm Tic Tac Toe is selected. Select Battleships by pressing the down
   arrow key on Windows or entering "s" on macOS/Linux. Press `Enter` on Windows or enter "e" on macOS/Linux. Confirm
   Battleships game is launched.

<!-- TODO: Cli args -->