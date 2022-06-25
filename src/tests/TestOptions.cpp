#include <iostream>
#include <slog/Options.h>

#define CHECK( TITLE, EXPR, CONDITION ) {\
    auto res = EXPR;\
    const char * bg = ( res CONDITION ) ? "\e[32;1m" : "\e[31;1m";\
    std::cout << #TITLE << " : " << bg << std::boolalpha << res << "\e[0m" << std::endl;\
}

int main( int args, const char ** argv )
{
    slog::Options opts = { { "init.str", std::string("init.value") }, { "node", slog::Options{ { "a", 1 }, { "b", 2 } } }  };
    opts.put<bool>( "bool", true );
    opts.put<char>( "char", 'c' );
    opts.put<int> ( "int" , 1 );
    opts.put<long>( "long", 2 );
    opts.put<std::string>( "string", std::string("str") );
    opts.put<slog::Level>( "level", slog::Level::MUTE );

    CHECK( "init.str", opts.get<std::string>("init.str"), == "init.value" )

    CHECK( "bool", opts.get<bool>("bool",false), == true )
    CHECK( "has bool", opts.has("bool"), == true )
    CHECK( "has xbool", opts.has("xbool"), == false )

    CHECK( "char", opts.get<char>("char"), == 'c' )
    CHECK( "int", opts.get<int>("int"), == 1 )
    CHECK( "long", opts.get<long>("long"), == 2 )
    CHECK( "string", opts.get<std::string>("string"), == "str" )
    CHECK( "level", opts.get<slog::Level>("level"), == slog::Level::MUTE )

    const slog::Options & node = opts.get<slog::Options>( "node" );
    CHECK( "node.int", node.get<int>("a"), == 1 )

}
