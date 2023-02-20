#include <algorithm>
#include <iostream>
#include <vector>
#include "includes/colored_cout.h"

const double cm_per_in = 2.54;

struct GameYaw {
    std::string game;
    double yaw;
};

const std::vector<GameYaw> GAME_YAWS = {
    {"source", 0.022},
    {"apex", 0.022},
    {"quake", 0.022},
    {"cs", 0.022},
    {"q3a", 0.022},
    {"bf5", 0.022},
    {"battlefield5", 0.022},
    {"d2", 0.0066},
    {"destiny2", 0.0066},
    {"ow", 0.0066},
    {"overwatch", 0.0066},
    {"fn", 0.5715},
    {"fortnite", 0.5715},
    {"ql", 0.02105},
    {"quakelive", 0.02105},
    {"pubg", 2.22222},
    {"ow2", 0.006666},
    {"overwatch2", 0.006666},
    {"doom", 0.0439453125},
    {"qcde", 0.0439453125},
    {"val", 0.051097900390625},
    {"valorant", 0.051097900390625},
    {"siege", 0.00572957795130823},
    {"r6", 0.00572957795130823},
    {"reflex", 0.00572957795130823},
    {"ut", 0.596}
};

// determine game and return the corresponding yaw
double determine_game( const std::string& game ) {
    auto identified_game = std::find_if(GAME_YAWS.begin(), GAME_YAWS.end(), [&]( const GameYaw& game_yaw ) { return game_yaw.game == game; });
    return ( identified_game != GAME_YAWS.end() ) ? identified_game->yaw : 0.0;
}

// calcs
// returns the cm value : ( ( 360 / ( yaw * sens ) ) / dpi * 2.54 )
void get_cm( double yaw, double sens, int dpi ) {
    auto inc = yaw * sens;
    auto counts_per_rev = 360 / inc;
    std::cout << " " << sens << " in game = " << clr::green << counts_per_rev / dpi * cm_per_in << clr::reset << " cm/360\n\n ";
    system( "pause" );
}

// returns the sens value : ( ( 360 / ( cm / 2.54 * dpi ) ) / yaw )
void get_sens( double yaw, double cm, int dpi ) {
    auto counts_per_rev = cm / cm_per_in * dpi;
    auto inc = 360 / counts_per_rev;
    std::cout << " " << cm << " cm/360 = " << clr::green << inc / yaw << clr::reset << " in game\n ";
    system( "pause" );
}

// game sens dpi -> cm/360
void cm() {
    std::string game;
    double input_game{};
    double input_sens;
    int input_dpi;

    while ( input_game == 0 ) {
        std::cout << " enter your desired game\n" << clr::green << "  > " << clr::reset;
        std::cin  >> game;
        input_game = determine_game( game );
    }

    std::cout << " enter your sensitivity\n" << clr::green << "  > " << clr::reset;
    std::cin  >> input_sens;
    std::cout << " enter your dpi\n" << clr::green << "  > " << clr::reset;
    std::cin  >> input_dpi;

    get_cm( input_game, input_sens, input_dpi );
}

// game1 game2 sens -> newsens
void convert() {
    std::string game1, game2;
    double input_game1{}, input_game2{};
    double input_sens;
    double conv;

    while ( input_game1 == 0 ) {
        std::cout << " enter the game you're converting from\n" << clr::green << "  > " << clr::reset;
        std::cin  >> game1;
        input_game1 = determine_game( game1 );
    }
    while ( input_game2 == 0 ) {
        std::cout << " enter the game you're converting to\n" << clr::green << "  > " << clr::reset;
        std::cin  >> game2;
        input_game2 = determine_game( game2 );
    }
    std::cout << " enter your sens\n" << clr::green << "  > " << clr::reset;
    std::cin  >> input_sens;

    conv = input_sens * input_game1;
    std::cout << " " << input_sens << " on " << game1 << " = " << clr::green << ( conv / input_game2 ) << clr::reset << " on " << game2 << "\n ";
    system( "pause" );
    std::cout << "\n";
}

// game cm dpi -> sens
void sens() {
    std::string game;
    double input_game{};
    double input_cm;
    int input_dpi;

    while ( input_game == 0 ) {
        std::cout << " enter your desired game\n" << clr::green << "  > " << clr::reset;
        std::cin  >> game;
        input_game = determine_game( game );
    }

    std::cout << " enter your cm\n"  << clr::green << "  > " << clr::reset;
    std::cin  >> input_cm;
    std::cout << " enter your dpi\n" << clr::green << "  > " << clr::reset;
    std::cin  >> input_dpi;

    get_sens( input_game, input_cm, input_dpi );
}

// outputs welcome message
void welcome() {
    system( "cls" );
    std::cout << clr::green << " senscalc" << clr::reset << " : tool for calculating sens or cm/360 within some games\n"
              << " type 'help' for direction\n"
              << clr::green << "  > " << clr::reset;
}

// outputs list of supported games
void games() {
    // sort the GAME_YAWS vector by yaw value
    std::vector<GameYaw> sorted = GAME_YAWS;
    std::sort(sorted.begin(), sorted.end(), []( const GameYaw& a, const GameYaw& b ) { return a.yaw < b.yaw;} );

    // group games with the same yaw value
    double current_yaw = -1;
    for ( const auto& gameYaw : sorted ) {
        if ( gameYaw.yaw != current_yaw ) {
            current_yaw = gameYaw.yaw;
            std::cout << "\n\t" << clr::green << current_yaw << clr::reset << ": \n\t\t";
        }
        else
            std::cout << ", ";
        std::cout << gameYaw.game;
    }
    std::cout << "\n";
    system( "pause" );
}

// outputs help text
void help() {
    std::cout << "\tcm \t "     << clr::green << "->" << clr::reset << " outputs cm/360 based on sens and game\n" // game sens dpi -> cm/360
              << "\tconvert\t " << clr::green << "->" << clr::reset << " converts sens between games\n"           // game1 game2 sens -> newsens
              << "\tsens \t "   << clr::green << "->" << clr::reset << " outputs sens based on game and dpi\n"    // game cm dpi -> sens
              << "\tgames \t "  << clr::green << "->" << clr::reset << " lists supported games\n"                 // list of supported games
              << "\texit \t "   << clr::green << "->" << clr::reset << " closes the application\n\n ";            // closes the calc
    system( "pause" );
}

// input
// initial menu comparatives
void menu( const std::string& input ) {
    if ( input == "cm" )      cm();
    if ( input == "convert" ) convert();
    if ( input == "sens" )    sens();
    if ( input == "games" )   games();
    if ( input == "help" )    help();
}

// main func
int main() {
    welcome();

    // take in input and loop
    std::string input;
    while ( std::cin >> input && input != "exit" ) {
        // call functions from input
        // executes function based on type of object
        menu( input );
        welcome();
    }

    return 0;
}