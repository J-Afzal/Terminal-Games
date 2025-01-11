#pragma once

#include <array>
#include <cstdint>
#include <exception>
#include <string>
#include <vector>

namespace TerminalGames::Globals
{
    namespace Exceptions
    {
        /**
         * @brief Used to quit the program.
         */
        class QuitProgram : public std::exception
        {};

        /**
         * @brief Used to quit the main menu.
         */
        class QuitMainMenu : public std::exception
        {};

        /**
         * @brief Used to quit a game.
         */
        class QuitGame : public std::exception
        {};

        /**
         * @brief Used to reset a game which prompts the user for new options.
         */
        class ResetGame : public std::exception
        {};

        /**
         * @brief Used to restart a game with the same user options.
         */
        class RestartGame : public std::exception
        {};

        /**
         * @brief Used when the backspace key is pressed.
         */
        class BackspaceKeyPressed : public std::exception
        {};

        /**
         * @brief Used when the hangman game words.txt file is not found.
         */
        class HangmanWordsNotFound : public std::exception
        {};

        /**
         * @brief Used for functionality that has not been implemented.
         */
        class NotImplementedError : public std::exception
        {};
    }

    /**
     * @brief Implements std::ranges::find and it should work for all std containers.
     * The std library version of this function is not supported by some compilers (usually because the function call fails
     * with GNU 12.2.0 within the CI workflow). Therefore it has been crudely implemented here for this project's specific
     * use case.
     *
     * @tparam T An std container.
     * @tparam U The type being stored by the std container.
     * @param p_begin The iterator returned from begin() function.
     * @param p_end The iterator returned from end() function.
     * @param p_value The value to find in the std container.
     * @return T Returns an iterator to the found value. If the value is not found then p_end is returned.
     */
    template<typename T, typename U>
    static T ImplementStdRangesFind(const T& p_begin, const T& p_end, const U& p_value) // NOLINT(bugprone-easily-swappable-parameters)
    {
        for (T i = p_begin; i < p_end; i++)
            if (*i == p_value)
                return i;

        return p_end;
    }

    /**
     * @brief Implements std::count and it should work for all std containers.
     * The std library version of this function is not supported by some compilers (usually because the function call fails
     * with GNU 12.2.0 within the CI workflow). Therefore it has been crudely implemented here for this project's specific
     * use case.
     *
     * @tparam T An std container.
     * @tparam U The type being stored by the std container.
     * @param p_begin The iterator returned from begin() function.
     * @param p_end The iterator returned from end() function.
     * @param p_value The value to count in the std container.
     * @return int32_t The number of occurrences of p_value in the input container.
     */
    template<typename T, typename U>
    static int32_t ImplementStdCount(const T& p_begin, const T& p_end, const U& p_value) // NOLINT(bugprone-easily-swappable-parameters)
    {
        int32_t count = 0;

        for (T i = p_begin; i < p_end; i++)
            if (*i == p_value)
                ++count;

        return count;
    }

    /**
     * @brief Crude implementation of std::format which only works for a single instance of '{}' in p_stringToFormat and
     * only a uint32_t as the variable to insert.
     * The std library version of this function is not supported by some compilers (usually because the function call fails
     * with GNU 12.2.0 within the CI workflow). Therefore it has been crudely implemented here for this project's specific
     * use case.
     *
     * @param p_stringToFormat The string which contains the '{}' to format.
     * @param p_varToInsert The integer to insert into the string.
     * @return std::string p_stringToFormat with p_varToInsert inserted in place of '{}'.
     */
    static std::string ImplementStdFormat(const std::string& p_stringToFormat, const uint32_t& p_varToInsert)
    {
        const std::string FORMAT_IDENTIFIER = "{}";
        const std::string BEFORE_STRING = p_stringToFormat.substr(0, p_stringToFormat.find(FORMAT_IDENTIFIER));
        const std::string AFTER_STRING = p_stringToFormat.substr(p_stringToFormat.find(FORMAT_IDENTIFIER) + FORMAT_IDENTIFIER.size(), p_stringToFormat.size() - p_stringToFormat.find("{}"));

        return BEFORE_STRING + std::to_string(p_varToInsert) + AFTER_STRING;
    }

    /**
     * @brief Homepage
     */
    inline static const std::string G_HOMEPAGE_TOP_TITLE = "Terminal Games";
    inline static const std::string G_HOMEPAGE_BOTTOM_TITLE = "q = quit program";
    static constexpr uint32_t G_HOMEPAGE_DISPLAY_WIDTH = 40;
    static constexpr uint32_t G_HOMEPAGE_DISPLAY_HEIGHT = 20;

    /**
     * @brief Main Menu
     */
    inline static const std::string G_MAIN_MENU_TOP_TITLE = "Main Menu";
    inline static const std::string G_MAIN_MENU_BOTTOM_TITLE = "q = quit to homepage";
    static constexpr uint32_t G_MAIN_MENU_DISPLAY_WIDTH = 32;
    static constexpr uint32_t G_MAIN_MENU_DISPLAY_HEIGHT = 13;

    /**
     * @brief Tic Tac Toe
     */
    inline static const std::string G_TICTACTOE_TOP_TITLE = "Tic Tac Toe";
    inline static const std::string G_TICTACTOE_BOTTOM_TITLE = "q = to show quit menu";
    static constexpr uint32_t G_TICTACTOE_DISPLAY_WIDTH = 58;
    static constexpr uint32_t G_TICTACTOE_DISPLAY_HEIGHT = 19;

    static constexpr uint32_t G_TICTACTOE_BOARD_WIDTH = 3;
    static constexpr uint32_t G_TICTACTOE_BOARD_HEIGHT = 3;

    static constexpr uint32_t G_TICTACTOE_GRID_ELEMENT_WIDTH = 4;
    static constexpr uint32_t G_TICTACTOE_GRID_ELEMENT_HEIGHT = 2;
    static constexpr uint32_t G_TICTACTOE_GRID_LEFT_PAD = 3;
    static constexpr uint32_t G_TICTACTOE_GRID_TOP_PAD = 4;

    static constexpr uint32_t G_TICTACTOE_MAXIMUM_ERROR_COUNT = G_TICTACTOE_BOARD_WIDTH * G_TICTACTOE_BOARD_HEIGHT;

    /**
     * @brief Hangman
     */
    inline static const std::string G_HANGMAN_TOP_TITLE = "Hangman";
    inline static const std::string G_HANGMAN_BOTTOM_TITLE = "q = to show quit menu";
    static constexpr uint32_t G_HANGMAN_DISPLAY_WIDTH = 64;
    static constexpr uint32_t G_HANGMAN_DISPLAY_HEIGHT = 22;

    static constexpr uint32_t G_HANGMAN_MINIMUM_WORD_SIZE = 3;
    static constexpr uint32_t G_HANGMAN_MAXIMUM_WORD_SIZE = 14;
    static constexpr uint32_t G_HANGMAN_MAXIMUM_ERROR_COUNT = 10;
    static constexpr uint32_t G_HANGMAN_KEY_PRESS_CHAR_OFFSET = 32;
    static constexpr uint32_t G_HANGMAN_NUMBER_OF_LETTERS_IN_THE_ALPHABET = 26;

    static constexpr uint32_t G_HANGMAN_USER_INPUT_ROW = 13;
    static constexpr uint32_t G_HANGMAN_GET_WORD_FROM_USER_COLUMN = 39;
    static constexpr uint32_t G_HANGMAN_GET_USER_COMMAND_COLUMN = 41;

    /**
     * @brief Battleships
     */
    inline static const std::string G_BATTLESHIPS_TOP_TITLE = "Battleships";
    inline static const std::string G_BATTLESHIPS_BOTTOM_TITLE = "q = to show quit menu";
    static constexpr uint32_t G_BATTLESHIPS_DISPLAY_WIDTH = 149;
    static constexpr uint32_t G_BATTLESHIPS_DISPLAY_HEIGHT = 38;

    static constexpr uint32_t G_BATTLESHIPS_BOARD_WIDTH = 10;
    static constexpr uint32_t G_BATTLESHIPS_BOARD_HEIGHT = 10;

    static constexpr uint32_t G_BATTLESHIPS_GRID_ELEMENT_WIDTH = 4;
    static constexpr uint32_t G_BATTLESHIPS_GRID_ELEMENT_HEIGHT = 2;
    static constexpr uint32_t G_BATTLESHIPS_GRID_LEFT_PAD = 10;
    static constexpr uint32_t G_BATTLESHIPS_GRID_TOP_PAD = 8;

    static constexpr uint32_t G_BATTLESHIPS_SHIP_COUNT = 5;

    static constexpr uint32_t G_BATTLESHIPS_CARRIER_SIZE = 5;
    static constexpr uint32_t G_BATTLESHIPS_BATTLESHIP_SIZE = 4;
    static constexpr uint32_t G_BATTLESHIPS_DESTROYER_SIZE = 3;
    static constexpr uint32_t G_BATTLESHIPS_SUBMARINE_SIZE = 3;
    static constexpr uint32_t G_BATTLESHIPS_PATROL_BOAT_SIZE = 2;

    inline static const std::string G_BATTLESHIPS_CARRIER_NAME = "Carrie";
    inline static const std::string G_BATTLESHIPS_BATTLESHIP_NAME = "Battleship";
    inline static const std::string G_BATTLESHIPS_DESTROYER_NAME = "Destroyer";
    inline static const std::string G_BATTLESHIPS_SUBMARINE_NAME = "Submarine";
    inline static const std::string G_BATTLESHIPS_PATROL_BOAT_NAME = "Patrol Boat";

    inline static const std::string G_BATTLESHIPS_PLACED_SHIP {static_cast<char>(178)};
    inline static const std::string G_BATTLESHIPS_SUCCESSFUL_ATTACK {static_cast<char>(176)};
    inline static const std::string G_BATTLESHIPS_MISSED_ATTACK {static_cast<char>(250)};

    inline static const std::array<std::string, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_NAMES = {
        G_BATTLESHIPS_CARRIER_NAME,
        G_BATTLESHIPS_BATTLESHIP_NAME,
        G_BATTLESHIPS_DESTROYER_NAME,
        G_BATTLESHIPS_SUBMARINE_NAME,
        G_BATTLESHIPS_PATROL_BOAT_NAME};

    inline static const std::array<uint32_t, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_SIZES = {
        G_BATTLESHIPS_CARRIER_SIZE,
        G_BATTLESHIPS_BATTLESHIP_SIZE,
        G_BATTLESHIPS_DESTROYER_SIZE,
        G_BATTLESHIPS_SUBMARINE_SIZE,
        G_BATTLESHIPS_PATROL_BOAT_SIZE};

    inline static const std::array<std::string, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_INSTRUCTIONS = {
        ImplementStdFormat("Please enter the {} grid locations for the Carrier", G_BATTLESHIPS_CARRIER_SIZE),
        ImplementStdFormat("Please enter the {} grid locations for the Battleship", G_BATTLESHIPS_BATTLESHIP_SIZE),
        ImplementStdFormat("Please enter the {} grid locations for the Destroyer", G_BATTLESHIPS_DESTROYER_SIZE),
        ImplementStdFormat("Please enter the {} grid locations for the Submarine", G_BATTLESHIPS_SUBMARINE_SIZE),
        ImplementStdFormat("Please enter the {} grid locations for the Patrol Boat", G_BATTLESHIPS_PATROL_BOAT_SIZE)};

    /**
     * @brief PageBuilder
     */
    // When highlighting what is currently selected in an option menu
    inline static const std::string G_SELECTOR = ">";

    // ANSI colour escape codes
    static constexpr uint32_t G_ANSI_COLOUR_ESCAPE_CODE_SIZE = 7;
    static constexpr char G_ANSI_COLOUR_ESCAPE_CODE_START = '\x1B';
    inline static const std::string G_RED_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;31m";
    inline static const std::string G_GREEN_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;32m";
    inline static const std::string G_YELLOW_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;33m";
    inline static const std::string G_BLUE_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;34m";
    inline static const std::string G_WHITE_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;37m";
    inline static const std::string G_RESET_ANSI_COLOUR_ESCAPE_CODE = "\x1B[0m";
    inline static const std::vector<std::string> G_ALL_ANSI_COLOUR_ESCAPE_CODES = {
        G_RED_ANSI_COLOUR_ESCAPE_CODE,
        G_GREEN_ANSI_COLOUR_ESCAPE_CODE,
        G_YELLOW_ANSI_COLOUR_ESCAPE_CODE,
        G_BLUE_ANSI_COLOUR_ESCAPE_CODE,
        G_WHITE_ANSI_COLOUR_ESCAPE_CODE,
        G_RESET_ANSI_COLOUR_ESCAPE_CODE,
    };

    inline static const std::vector<std::string> G_QUIT_MENU_OPTIONS = {
        "Restart Game",
        "Reset Game",
        "Quit to Main Menu",
        "Quit to Homepage",
        "Quit Program",
        "Cancel",
    };

    static constexpr uint32_t G_RESTART_GAME_INDEX = 0;
    static constexpr uint32_t G_RESET_GAME_INDEX = 1;
    static constexpr uint32_t G_QUIT_GAME_INDEX = 2;
    static constexpr uint32_t G_QUIT_MAIN_MENU_INDEX = 3;
    static constexpr uint32_t G_QUIT_PROGRAM_INDEX = 4;
    static constexpr uint32_t G_CANCEL_INDEX = 5;

    // Extended ASCII characters for edges and corners of the page
    static constexpr char G_HORIZONTAL_LINE = static_cast<char>(205);
    static constexpr char G_VERTICAL_LINE = static_cast<char>(186);
    static constexpr char G_TOP_RIGHT_CORNER = static_cast<char>(187);
    static constexpr char G_BOTTOM_RIGHT_CORNER = static_cast<char>(188);
    static constexpr char G_BOTTOM_LEFT_CORNER = static_cast<char>(200);
    static constexpr char G_TOP_LEFT_CORNER = static_cast<char>(201);

    // Padding
    static constexpr uint32_t G_MINIMUM_LEFT_VERTICAL_LINE_SIZE = 1;
    static constexpr uint32_t G_MINIMUM_LEFT_PADDING_SIZE = 1;
    static constexpr uint32_t G_MINIMUM_RIGHT_PADDING_SIZE = 1;
    static constexpr uint32_t G_MINIMUM_RIGHT_VERTICAL_LINE_SIZE = 1;

    /**
     * @brief Terminal
     */
    // Keyboard values when getting user input on Windows
    static constexpr uint32_t G_ENTER_KEY = '\r';
    static constexpr uint32_t G_BACKSPACE_KEY = 8;
    static constexpr uint32_t G_UP_ARROW_KEY = 72;
    static constexpr uint32_t G_DOWN_ARROW_KEY = 80;
    static constexpr uint32_t G_LEFT_ARROW_KEY = 75;
    static constexpr uint32_t G_RIGHT_ARROW_KEY = 77;
    static constexpr uint32_t G_QUIT_KEY = 'q';
    static constexpr uint32_t G_RESTART_KEY = 'r';

    // Cursor width while running on windows.
    static constexpr uint32_t G_CURSOR_WIDTH_PERCENTAGE = 100;

    // Keyboard values when getting user input on other platforms
    static constexpr uint32_t G_ALTERNATIVE_ENTER_KEY = 'e';
    static constexpr uint32_t G_ALTERNATIVE_BACKSPACE_KEY = 'z';
    static constexpr uint32_t G_ALTERNATIVE_UP_ARROW_KEY = 'w';
    static constexpr uint32_t G_ALTERNATIVE_DOWN_ARROW_KEY = 's';
    static constexpr uint32_t G_ALTERNATIVE_LEFT_ARROW_KEY = 'a';
    static constexpr uint32_t G_ALTERNATIVE_RIGHT_ARROW_KEY = 'd';

    /**
     * @brief Hangman word list for the computer
     */
    static constexpr uint32_t G_NUMBER_OF_WORDS = 972;
    inline static const std::array<std::string, G_NUMBER_OF_WORDS> G_HANGMAN_COMPUTER_WORDS = {
        "ABILITY",
        "ABLE",
        "ABOUT",
        "ABOVE",
        "ACCEPT",
        "ACCORDING",
        "ACCOUNT",
        "ACROSS",
        "ACT",
        "ACTION",
        "ACTIVITY",
        "ACTUALLY",
        "ADD",
        "ADDRESS",
        "ADMINISTRATION",
        "ADMIT",
        "ADULT",
        "AFFECT",
        "AFTER",
        "AGAIN",
        "AGAINST",
        "AGE",
        "AGENCY",
        "AGENT",
        "AGO",
        "AGREE",
        "AGREEMENT",
        "AHEAD",
        "AIR",
        "ALL",
        "ALLOW",
        "ALMOST",
        "ALONE",
        "ALONG",
        "ALREADY",
        "ALSO",
        "ALTHOUGH",
        "ALWAYS",
        "AMERICAN",
        "AMONG",
        "AMOUNT",
        "ANALYSIS",
        "AND",
        "ANIMAL",
        "ANOTHER",
        "ANSWER",
        "ANY",
        "ANYONE",
        "ANYTHING",
        "APPEAR",
        "APPLY",
        "APPROACH",
        "AREA",
        "ARGUE",
        "ARM",
        "AROUND",
        "ARRIVE",
        "ART",
        "ARTICLE",
        "ARTIST",
        "ASK",
        "ASSUME",
        "ATTACK",
        "ATTENTION",
        "ATTORNEY",
        "AUDIENCE",
        "AUTHOR",
        "AUTHORITY",
        "AVAILABLE",
        "AVOID",
        "AWAY",
        "BABY",
        "BACK",
        "BAD",
        "BAG",
        "BALL",
        "BANK",
        "BAR",
        "BASE",
        "BEAT",
        "BEAUTIFUL",
        "BECAUSE",
        "BECOME",
        "BED",
        "BEFORE",
        "BEGIN",
        "BEHAVIOUR",
        "BEHIND",
        "BELIEVE",
        "BENEFIT",
        "BEST",
        "BETTER",
        "BETWEEN",
        "BEYOND",
        "BIG",
        "BILL",
        "BILLION",
        "BIT",
        "BLACK",
        "BLOOD",
        "BLUE",
        "BOARD",
        "BODY",
        "BOOK",
        "BORN",
        "BOTH",
        "BOX",
        "BOY",
        "BREAK",
        "BRING",
        "BROTHER",
        "BUDGET",
        "BUILD",
        "BUILDING",
        "BUSINESS",
        "BUT",
        "BUY",
        "CALL",
        "CAMERA",
        "CAMPAIGN",
        "CAN",
        "CANCER",
        "CANDIDATE",
        "CAPITAL",
        "CAR",
        "CARD",
        "CARE",
        "CAREER",
        "CARRY",
        "CASE",
        "CATCH",
        "CAUSE",
        "CELL",
        "CENTER",
        "CENTRAL",
        "CENTURY",
        "CERTAIN",
        "CERTAINLY",
        "CHAIR",
        "CHALLENGE",
        "CHANCE",
        "CHANGE",
        "CHARACTER",
        "CHARGE",
        "CHECK",
        "CHILD",
        "CHOICE",
        "CHOOSE",
        "CHURCH",
        "CITIZEN",
        "CITY",
        "CIVIL",
        "CLAIM",
        "CLASS",
        "CLEAR",
        "CLEARLY",
        "CLOSE",
        "COACH",
        "COLD",
        "COLLECTION",
        "COLLEGE",
        "COLOUR",
        "COME",
        "COMMERCIAL",
        "COMMON",
        "COMMUNITY",
        "COMPANY",
        "COMPARE",
        "COMPUTER",
        "CONCERN",
        "CONDITION",
        "CONFERENCE",
        "CONGRESS",
        "CONSIDER",
        "CONSUMER",
        "CONTAIN",
        "CONTINUE",
        "CONTROL",
        "COST",
        "COULD",
        "COUNTRY",
        "COUPLE",
        "COURSE",
        "COURT",
        "COVER",
        "CREATE",
        "CRIME",
        "CULTURAL",
        "CULTURE",
        "CUP",
        "CURRENT",
        "CUSTOMER",
        "CUT",
        "DARK",
        "DATA",
        "DAUGHTER",
        "DAY",
        "DEAD",
        "DEAL",
        "DEATH",
        "DEBATE",
        "DECADE",
        "DECIDE",
        "DECISION",
        "DEEP",
        "DEFENCE",
        "DEGREE",
        "DEMOCRAT",
        "DEMOCRATIC",
        "DESCRIBE",
        "DESIGN",
        "DESPITE",
        "DETAIL",
        "DETERMINE",
        "DEVELOP",
        "DEVELOPMENT",
        "DIE",
        "DIFFERENCE",
        "DIFFERENT",
        "DIFFICULT",
        "DINNER",
        "DIRECTION",
        "DIRECTOR",
        "DISCOVER",
        "DISCUSS",
        "DISCUSSION",
        "DISEASE",
        "DOCTOR",
        "DOG",
        "DOOR",
        "DOWN",
        "DRAW",
        "DREAM",
        "DRIVE",
        "DROP",
        "DRUG",
        "DURING",
        "EACH",
        "EARLY",
        "EAST",
        "EASY",
        "EAT",
        "ECONOMIC",
        "ECONOMY",
        "EDGE",
        "EDUCATION",
        "EFFECT",
        "EFFORT",
        "EIGHT",
        "EITHER",
        "ELECTION",
        "ELSE",
        "EMPLOYEE",
        "END",
        "ENERGY",
        "ENJOY",
        "ENOUGH",
        "ENTER",
        "ENTIRE",
        "ENVIRONMENT",
        "ENVIRONMENTAL",
        "ESPECIALLY",
        "ESTABLISH",
        "EVEN",
        "EVENING",
        "EVENT",
        "EVER",
        "EVERY",
        "EVERYBODY",
        "EVERYONE",
        "EVERYTHING",
        "EVIDENCE",
        "EXACTLY",
        "EXAMPLE",
        "EXECUTIVE",
        "EXIST",
        "EXPECT",
        "EXPERIENCE",
        "EXPERT",
        "EXPLAIN",
        "EYE",
        "FACE",
        "FACT",
        "FACTOR",
        "FAIL",
        "FALL",
        "FAMILY",
        "FAR",
        "FAST",
        "FATHER",
        "FEAR",
        "FEDERAL",
        "FEEL",
        "FEELING",
        "FEW",
        "FIELD",
        "FIGHT",
        "FIGURE",
        "FILL",
        "FILM",
        "FINAL",
        "FINALLY",
        "FINANCIAL",
        "FIND",
        "FINE",
        "FINGER",
        "FINISH",
        "FIRE",
        "FIRM",
        "FIRST",
        "FISH",
        "FIVE",
        "FLOOR",
        "FLY",
        "FOCUS",
        "FOLLOW",
        "FOOD",
        "FOOT",
        "FOR",
        "FORCE",
        "FOREIGN",
        "FORGET",
        "FORM",
        "FORMER",
        "FORWARD",
        "FOUR",
        "FREE",
        "FRIEND",
        "FROM",
        "FRONT",
        "FULL",
        "FUND",
        "FUTURE",
        "GAME",
        "GARDEN",
        "GAS",
        "GENERAL",
        "GENERATION",
        "GET",
        "GIRL",
        "GIVE",
        "GLASS",
        "GOAL",
        "GOOD",
        "GOVERNMENT",
        "GREAT",
        "GREEN",
        "GROUND",
        "GROUP",
        "GROW",
        "GROWTH",
        "GUESS",
        "GUN",
        "GUY",
        "HAIR",
        "HALF",
        "HAND",
        "HANG",
        "HAPPEN",
        "HAPPY",
        "HARD",
        "HAVE",
        "HEAD",
        "HEALTH",
        "HEAR",
        "HEART",
        "HEAT",
        "HEAVY",
        "HELP",
        "HER",
        "HERE",
        "HERSELF",
        "HIGH",
        "HIM",
        "HIMSELF",
        "HIS",
        "HISTORY",
        "HIT",
        "HOLD",
        "HOME",
        "HOPE",
        "HOSPITAL",
        "HOT",
        "HOTEL",
        "HOUR",
        "HOUSE",
        "HOW",
        "HOWEVER",
        "HUGE",
        "HUMAN",
        "HUNDRED",
        "HUSBAND",
        "IDEA",
        "IDENTIFY",
        "IMAGE",
        "IMAGINE",
        "IMPACT",
        "IMPORTANT",
        "IMPROVE",
        "INCLUDE",
        "INCLUDING",
        "INCREASE",
        "INDEED",
        "INDICATE",
        "INDIVIDUAL",
        "INDUSTRY",
        "INFORMATION",
        "INSIDE",
        "INSTEAD",
        "INSTITUTION",
        "INTEREST",
        "INTERESTING",
        "INTERNATIONAL",
        "INTERVIEW",
        "INTO",
        "INVESTMENT",
        "INVOLVE",
        "ISSUE",
        "ITEM",
        "ITS",
        "ITSELF",
        "JOB",
        "JOIN",
        "JUST",
        "KEEP",
        "KEY",
        "KID",
        "KILL",
        "KIND",
        "KITCHEN",
        "KNOW",
        "KNOWLEDGE",
        "LAND",
        "LANGUAGE",
        "LARGE",
        "LAST",
        "LATE",
        "LATER",
        "LAUGH",
        "LAW",
        "LAWYER",
        "LAY",
        "LEAD",
        "LEADER",
        "LEARN",
        "LEAST",
        "LEAVE",
        "LEFT",
        "LEG",
        "LEGAL",
        "LESS",
        "LET",
        "LETTER",
        "LEVEL",
        "LIE",
        "LIFE",
        "LIGHT",
        "LIKE",
        "LIKELY",
        "LINE",
        "LIST",
        "LISTEN",
        "LITTLE",
        "LIVE",
        "LOCAL",
        "LONG",
        "LOOK",
        "LOSE",
        "LOSS",
        "LOT",
        "LOVE",
        "LOW",
        "MACHINE",
        "MAGAZINE",
        "MAIN",
        "MAINTAIN",
        "MAJOR",
        "MAJORITY",
        "MAKE",
        "MAN",
        "MANAGE",
        "MANAGEMENT",
        "MANAGER",
        "MANY",
        "MARKET",
        "MARRIAGE",
        "MATERIAL",
        "MATTER",
        "MAY",
        "MAYBE",
        "MEAN",
        "MEASURE",
        "MEDIA",
        "MEDICAL",
        "MEET",
        "MEETING",
        "MEMBER",
        "MEMORY",
        "MENTION",
        "MESSAGE",
        "METHOD",
        "MIDDLE",
        "MIGHT",
        "MILITARY",
        "MILLION",
        "MIND",
        "MINUTE",
        "MISS",
        "MISSION",
        "MODEL",
        "MODERN",
        "MOMENT",
        "MONEY",
        "MONTH",
        "MORE",
        "MORNING",
        "MOST",
        "MOTHER",
        "MOUTH",
        "MOVE",
        "MOVEMENT",
        "MOVIE",
        "MRS",
        "MUCH",
        "MUSIC",
        "MUST",
        "MYSELF",
        "NAME",
        "NATION",
        "NATIONAL",
        "NATURAL",
        "NATURE",
        "NEAR",
        "NEARLY",
        "NECESSARY",
        "NEED",
        "NETWORK",
        "NEVER",
        "NEW",
        "NEWS",
        "NEWSPAPER",
        "NEXT",
        "NICE",
        "NIGHT",
        "NONE",
        "NOR",
        "NORTH",
        "NOT",
        "NOTE",
        "NOTHING",
        "NOTICE",
        "NOW",
        "N'T",
        "NUMBER",
        "OCCUR",
        "OFF",
        "OFFER",
        "OFFICE",
        "OFFICER",
        "OFFICIAL",
        "OFTEN",
        "OIL",
        "OLD",
        "ONCE",
        "ONE",
        "ONLY",
        "ONTO",
        "OPEN",
        "OPERATION",
        "OPPORTUNITY",
        "OPTION",
        "ORDER",
        "ORGANIZATION",
        "OTHER",
        "OTHERS",
        "OUR",
        "OUT",
        "OUTSIDE",
        "OVER",
        "OWN",
        "OWNER",
        "PAGE",
        "PAIN",
        "PAINTING",
        "PAPER",
        "PARENT",
        "PART",
        "PARTICIPANT",
        "PARTICULAR",
        "PARTICULARLY",
        "PARTNER",
        "PARTY",
        "PASS",
        "PAST",
        "PATIENT",
        "PATTERN",
        "PAY",
        "PEACE",
        "PEOPLE",
        "PER",
        "PERFORM",
        "PERFORMANCE",
        "PERHAPS",
        "PERIOD",
        "PERSON",
        "PERSONAL",
        "PHONE",
        "PHYSICAL",
        "PICK",
        "PICTURE",
        "PIECE",
        "PLACE",
        "PLAN",
        "PLANT",
        "PLAY",
        "PLAYER",
        "POINT",
        "POLICE",
        "POLICY",
        "POLITICAL",
        "POLITICS",
        "POOR",
        "POPULAR",
        "POPULATION",
        "POSITION",
        "POSITIVE",
        "POSSIBLE",
        "POWER",
        "PRACTICE",
        "PREPARE",
        "PRESENT",
        "PRESIDENT",
        "PRESSURE",
        "PRETTY",
        "PREVENT",
        "PRICE",
        "PRIVATE",
        "PROBABLY",
        "PROBLEM",
        "PROCESS",
        "PRODUCE",
        "PRODUCT",
        "PRODUCTION",
        "PROFESSIONAL",
        "PROFESSOR",
        "PROGRAM",
        "PROJECT",
        "PROPERTY",
        "PROTECT",
        "PROVE",
        "PROVIDE",
        "PUBLIC",
        "PULL",
        "PURPOSE",
        "PUSH",
        "PUT",
        "QUALITY",
        "QUESTION",
        "QUICKLY",
        "QUITE",
        "RACE",
        "RADIO",
        "RAISE",
        "RANGE",
        "RATE",
        "RATHER",
        "REACH",
        "READ",
        "READY",
        "REAL",
        "REALITY",
        "REALIZE",
        "REALLY",
        "REASON",
        "RECEIVE",
        "RECENT",
        "RECENTLY",
        "RECOGNIZE",
        "RECORD",
        "RED",
        "REDUCE",
        "REFLECT",
        "REGION",
        "RELATE",
        "RELATIONSHIP",
        "RELIGIOUS",
        "REMAIN",
        "REMEMBER",
        "REMOVE",
        "REPORT",
        "REPRESENT",
        "REPUBLICAN",
        "REQUIRE",
        "RESEARCH",
        "RESOURCE",
        "RESPOND",
        "RESPONSE",
        "RESPONSIBILITY",
        "REST",
        "RESULT",
        "RETURN",
        "REVEAL",
        "RICH",
        "RIGHT",
        "RISE",
        "RISK",
        "ROAD",
        "ROCK",
        "ROLE",
        "ROOM",
        "RULE",
        "RUN",
        "SAFE",
        "SAME",
        "SAVE",
        "SAY",
        "SCENE",
        "SCHOOL",
        "SCIENCE",
        "SCIENTIST",
        "SCORE",
        "SEA",
        "SEASON",
        "SEAT",
        "SECOND",
        "SECTION",
        "SECURITY",
        "SEE",
        "SEEK",
        "SEEM",
        "SELL",
        "SEND",
        "SENIOR",
        "SENSE",
        "SERIES",
        "SERIOUS",
        "SERVE",
        "SERVICE",
        "SET",
        "SEVEN",
        "SEVERAL",
        "SEX",
        "SEXUAL",
        "SHAKE",
        "SHARE",
        "SHE",
        "SHOOT",
        "SHORT",
        "SHOT",
        "SHOULD",
        "SHOULDER",
        "SHOW",
        "SIDE",
        "SIGN",
        "SIGNIFICANT",
        "SIMILAR",
        "SIMPLE",
        "SIMPLY",
        "SINCE",
        "SING",
        "SINGLE",
        "SISTER",
        "SIT",
        "SITE",
        "SITUATION",
        "SIX",
        "SIZE",
        "SKILL",
        "SKIN",
        "SMALL",
        "SMILE",
        "SOCIAL",
        "SOCIETY",
        "SOLDIER",
        "SOME",
        "SOMEBODY",
        "SOMEONE",
        "SOMETHING",
        "SOMETIMES",
        "SON",
        "SONG",
        "SOON",
        "SORT",
        "SOUND",
        "SOURCE",
        "SOUTH",
        "SOUTHERN",
        "SPACE",
        "SPEAK",
        "SPECIAL",
        "SPECIFIC",
        "SPEECH",
        "SPEND",
        "SPORT",
        "SPRING",
        "STAFF",
        "STAGE",
        "STAND",
        "STANDARD",
        "STAR",
        "START",
        "STATE",
        "STATEMENT",
        "STATION",
        "STAY",
        "STEP",
        "STILL",
        "STOCK",
        "STOP",
        "STORE",
        "STORY",
        "STRATEGY",
        "STREET",
        "STRONG",
        "STRUCTURE",
        "STUDENT",
        "STUDY",
        "STUFF",
        "STYLE",
        "SUBJECT",
        "SUCCESS",
        "SUCCESSFUL",
        "SUCH",
        "SUDDENLY",
        "SUFFER",
        "SUGGEST",
        "SUMMER",
        "SUPPORT",
        "SURE",
        "SURFACE",
        "SYSTEM",
        "TABLE",
        "TAKE",
        "TALK",
        "TASK",
        "TAX",
        "TEACH",
        "TEACHER",
        "TEAM",
        "TECHNOLOGY",
        "TELEVISION",
        "TELL",
        "TEN",
        "TEND",
        "TERM",
        "TEST",
        "THAN",
        "THANK",
        "THAT",
        "THE",
        "THEIR",
        "THEM",
        "THEMSELVES",
        "THEN",
        "THEORY",
        "THERE",
        "THESE",
        "THEY",
        "THING",
        "THINK",
        "THIRD",
        "THIS",
        "THOSE",
        "THOUGH",
        "THOUGHT",
        "THOUSAND",
        "THREAT",
        "THREE",
        "THROUGH",
        "THROUGHOUT",
        "THROW",
        "THUS",
        "TIME",
        "TODAY",
        "TOGETHER",
        "TONIGHT",
        "TOO",
        "TOP",
        "TOTAL",
        "TOUGH",
        "TOWARD",
        "TOWN",
        "TRADE",
        "TRADITIONAL",
        "TRAINING",
        "TRAVEL",
        "TREAT",
        "TREATMENT",
        "TREE",
        "TRIAL",
        "TRIP",
        "TROUBLE",
        "TRUE",
        "TRUTH",
        "TRY",
        "TURN",
        "TWO",
        "TYPE",
        "UNDER",
        "UNDERSTAND",
        "UNIT",
        "UNTIL",
        "UPON",
        "USE",
        "USUALLY",
        "VALUE",
        "VARIOUS",
        "VERY",
        "VICTIM",
        "VIEW",
        "VIOLENCE",
        "VISIT",
        "VOICE",
        "VOTE",
        "WAIT",
        "WALK",
        "WALL",
        "WANT",
        "WAR",
        "WATCH",
        "WATER",
        "WAY",
        "WEAPON",
        "WEAR",
        "WEEK",
        "WEIGHT",
        "WELL",
        "WEST",
        "WESTERN",
        "WHAT",
        "WHATEVER",
        "WHEN",
        "WHERE",
        "WHETHER",
        "WHICH",
        "WHILE",
        "WHITE",
        "WHO",
        "WHOLE",
        "WHOM",
        "WHOSE",
        "WHY",
        "WIDE",
        "WIFE",
        "WILL",
        "WIN",
        "WIND",
        "WINDOW",
        "WISH",
        "WITH",
        "WITHIN",
        "WITHOUT",
        "WOMAN",
        "WONDER",
        "WORD",
        "WORK",
        "WORKER",
        "WORLD",
        "WORRY",
        "WOULD",
        "WRITE",
        "WRITER",
        "WRONG",
        "YARD",
        "YEAH",
        "YEAR",
        "YES",
        "YET",
        "YOU",
        "YOUNG",
        "YOUR",
        "YOURSELF",
    };
}
