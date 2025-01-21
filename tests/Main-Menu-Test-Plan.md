# Main Menu Test Plan

## Available Screens

### Windows

#### Windows Using ANSI Colour Escape Codes

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
║ > Yes                                ║
║   No                                 ║
╚══════════════════════════════════════╝
╔══════════════════════════════════════╗
║           q = quit program           ║
╚══════════════════════════════════════╝
```

> [!NOTE]
> The output should be coloured.

#### Windows Using Only ASCII Characters

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
```

### Other Platforms

#### Other Platforms Using ANSI Colour Escape Codes

```text
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

#### Other Platforms Using Only ASCII Characters

```text
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

## Initial Page

1. Run MainMenu via CLI constructor on Windows with no options set:

   Run MainMenu via constructor on Windows with `p_useAnsiEscapeCodes` set to `false`:

   Run `terminal-games.exe` with any argument other that `--h`, -`--help`, `--a`, `--ascii-only`:



2. Run MainMenu via CLI constructor on Windows with `--a` as the only argument:

   Run MainMenu via CLI constructor on Windows with `--ascii-only` as the only argument:

   Run MainMenu via constructor with `p_useAnsiEscapeCodes` set to `true`:

   Run `terminal-games.exe` with `--a` argument:

   Run `terminal-games.exe` with `--ascii-only` argument:



3. Press `q` on Windows or enter "q" on macOS/Linux. Confirm the program terminates.

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

## CLI Usage

1. Run the following command on Windows `terminal-games.exe`:

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
    ║ > Yes                                ║
    ║   No                                 ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           q = quit program           ║
    ╚══════════════════════════════════════╝
    ```

    > [!NOTE]
    > The output should be coloured.

1. Run the following commands on Windows and confirm the below is outputted:

    `terminal-games.exe --h`

    `terminal-games.exe --help`

    ```text

    Usage: terminal-games [options]

    OPTIONS:

    Generic Options:

    --h --help        Display available options.

    terminal-games options:

    --a --ascii-only  Only use ASCII characters (this removes all colour).

    ```

1. Run the following commands on Windows and confirm the below is outputted:

   `terminal-games.exe --a`

   `terminal-games.exe --ascii-only`

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
   ```

1. Pass any other arguments to `terminal-games.exe` and confirm the below is outputted:

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
    ║ > Yes                                ║
    ║   No                                 ║
    ╚══════════════════════════════════════╝
    ╔══════════════════════════════════════╗
    ║           q = quit program           ║
    ╚══════════════════════════════════════╝
    ```

    > [!NOTE]
    > The output should be coloured.
