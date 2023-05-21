#include <iostream>
#include <ctime>

void entry_prompt()
{
    std::cout << "╔════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << std::endl;
    std::cout << "                        ...',;;:cccccccc:;,.." << std::endl;
    std::cout << "                    ..,;:cccc::::ccccclloooolc;'." << std::endl;
    std::cout << "                 .',;:::;;;;:loodxk0kkxxkxxdocccc;;'.." << std::endl;
    std::cout << "               .,;;;,,;:coxldKNWWWMMMMWNNWWNNKkdolcccc:,." << std::endl;
    std::cout << "            .',;;,',;lxo:...dXWMMMMMMMMNkloOXNNNX0koc:coo;." << std::endl;
    std::cout << "         ..,;:;,,,:ldl'   .kWMMMWXXNWMMMMXd..':d0XWWN0d:;lkd," << std::endl;
    std::cout << "       ..,;;,,'':loc.     lKMMMNl. .c0KNWNK:  ..';lx00X0l,cxo,." << std::endl;
    std::cout << "     ..''....'cooc.       c0NMMX;   .l0XWN0;       ,ddx00occl:." << std::endl;
    std::cout << "   ..'..  .':odc.         .x0KKKkolcld000xc.       .cxxxkkdl:,.." << std::endl;
    std::cout << " ..''..   ;dxolc;'         .lxx000kkxx00kc.      .;looolllol:'.." << std::endl;
    std::cout << "..'..    .':lloolc:,..       'lxkkkkk0kd,   ..':clc:::;,,;:;,'.." << std::endl;
    std::cout << "......   ....',;;;:ccc::;;,''',:loddol:,,;:clllolc:;;,'........" << std::endl;
    std::cout << "    .     ....'''',,,;;:cccccclllloooollllccc:c:::;,'.." << std::endl;
    std::cout << "            .......'',,,,,,,,;;::::ccccc::::;;;,,''..." << std::endl;
    std::cout << "              ...............''',,,;;;,,''''''......" << std::endl;
    std::cout << "                   ............................" << std::endl;
    std::cout << std::endl;
    std::cout << "  Without freedom of thought; there can be no such thing as wisdom;" << std::endl;
    std::cout << "   and no such thing as public liberty, without freedom of speech." << std::endl;
    std::cout << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

void category_prompt()
{
    std::cout << "Select a category:" << std::endl;
    std::cout << "[0] - Exit program" << std::endl;
    std::cout << "[1] - Key management" << std::endl;
    std::cout << "[2] - Key operations" << std::endl;
    std::cout << std::endl;
}

void key_management_prompt()
{
    std::cout << "Select an operation:" << std::endl;
    std::cout << "[0] - Back" << std::endl;
    std::cout << "[1] - Generate keypair" << std::endl;
    std::cout << "[2] - Read keys" << std::endl;
    std::cout << "[3] - Write keys" << std::endl;
    std::cout << "[4] - Print public key" << std::endl;
    std::cout << "[5] - Print public key" << std::endl;
    std::cout << std::endl;
}

void key_operations_prompt()
{
    std::cout << "Select an operation:" << std::endl;
    std::cout << "[0] - Back" << std::endl;
    std::cout << std::endl;
}

void invalid_prompt()
{
    std::cout << "Invalid input." << std::endl;
    std::cout << std::endl;
}

void exit_prompt()
{
    srand(time(NULL));
    int quote_count = 12; 
    int random_index = rand() % quote_count;
    std::string exit_quotes[quote_count] = {
        "Be well, do good work, and keep in touch.",
        "Farewell, my friend, till we meet again someday somewhere.",
        "Whatever you do in life, surround yourself with smart people who'll argue with you.",
        "Our lives begin to end the day we become silent about things that matter.",
        "Find more pleasure in intelligent dissent than in passive aggreement.",
        "Too often we enjoy the comfort of opinion without the discomfort of thought.",
        "You can't cross the sea merely by standing and staring at the water.",
        "Stand before the people you fear and speak your mind - even if your voice shakes.",
        "Censorship reflects a society's lack of confidence in itself.",
        "Any book worth banning is a book worth reading.",
        "A truly great library has something to offend everyone.",
        "We must never forget the horrors which an unchecked hatred can lead."
    };
    std::cout << exit_quotes[random_index] << std::endl;
    std::cout << std::endl;
}

int main()
{
    entry_prompt();

    // Init memory
    int input;

    // Explicitly goto category loop
    goto category_loop;

    // Loops
    // [
    category_loop:
        category_prompt();
        std::cin >> input;
        std::cout << std::endl;
        goto category_process;

    key_management_loop:
        key_management_prompt();
        std::cin >> input;
        std::cout << std::endl;
        goto key_management_process;

    key_operations_loop:
        key_operations_prompt();
        std::cin >> input;
        std::cout << std::endl;
        goto key_operations_process;
    // ]

    // Input processors
    // [
    category_process:
        if (input == 0) goto exit;
        if (input == 1) goto key_management_loop;
        if (input == 2) goto key_operations_loop;
        invalid_prompt();
        goto category_loop;

    key_management_process:
        if (input == 0) goto category_loop;
        invalid_prompt();
        goto key_management_loop;
    
    key_operations_process:
        if (input == 0) goto category_loop;
        invalid_prompt();
        goto key_operations_loop;
    // ]

    exit:
        exit_prompt();
        return 1;
}
