#pragma once

#include <vector>
#include <string>
namespace aoc2024::day12
{
inline std::vector<std::string> input()
{
    return { // clang-format off
        "UCCCCCHHHGGGGHHHPPPPPPPPDGGDDDDBKKKKKKKKKKKKKKKWWWWWWWWWGGGLLLLLLLLLZZZRTDDTTKIIIMIXXXXXAAAAAAAAAAARRRRRRRRUZUUUUUUTTTTTTTTTTTTYYRRRRRRRRRRR",
        "UUUCCHQHHHHHHHPPPPPPPPPDDDDDDDDDKKKKKKKKKKKKKKWWWWWWWWWWWWWWLLLLLLLMZZTTTTTTTTIIIIIIIXXAAAAAAAAAAAAARRRRRRRUUUUUUUUTTTTTTTTTTTTTRRRRRRRRRRRR",
        "UUUCCHHHHHHHHHPPPPPPPPPDDDDDDDDDKKKKKKKKKKKKKKWWWWWWWWWWWLWWLLLLLJJQQTBTTTTTTIIIIIIIIIIYAAAAAAAAAAAAARRRRUUUUUUUUUUTTTTTTTTTTTTTERRIRRRRRRRR",
        "UUUCHHHHHHHHYHPPPPPPPPDDDDDDDDDDKKKKKKKKKKKWWWWWWWWWWWWWWLLLLLLLLLQQQTTTTTTTTIIIIIIIIIIAAAAAAAAAAAAAARRRRRUUUUUUUUTTTTTTTTTTTTTTEEEIIIRRRRRR",
        "UUUUUHHHHHHHHPPPPPPFFPPDDDDDDDDDKKKKKKKKKKKWWWWWWWWWWWWWWLLLLLLQQQQQQQTTTTTTIIIIIIIIIIIIIIAIAAAAAAAAARRRUUUUUUUUUUTTBTTTTTTTTYTEEEEIIRRRRRRR",
        "UUUUFHHHHHHHHHPPPFFFCDDDDDDDDDDDDDDPKKKKKKKKKKWIIWWQQWLLLLLLLLLQQQQQQQTTTTTTTTIIIIIIIIIIIIAIAAAAAAAAARRRUUUUQQQQUUTUUUTVTTTTTTEEEIIIIIIRRRRR",
        "UUUUUHHHHHHHHPPPPFFFFDDDDDDDDDDDDDPPPKKKKKKKKHWHIIWWWWLLLLLLLLLQQQQQTQTTTTTTTTIIIIIIIIIIIIIIAAAAAAAARRRRUUBBQQUUUUUUUUUVTTYTYTTEEIIIIIIIRRRR",
        "UUUUUHHHHHHHMPMPPFFFFDDDDDDDDTTTDDPPPPKKKKKKHHHHHHHWWQLLLLLLLLLQQQQQTTTTTTTTTTIIIIIIIIIIIIIIAAAAAAARRRNRRUUBQQQUUUUUUUUUTYYTYTTEEEIIIIIRRRRR",
        "UUUUUHHHHHMMMMMMMNNFFCDDDDDDDDDTPIPPPPPPPPKKHHHHHHHHWQLLLLLLLLLQQGGQQQTTTTTTTTTIIIIIIIIIIIIIAAAAAAFNNNNNRRQQQQQQUUUUUUUUTYYYYIIEIEIIIIIRRRRR",
        "UUUUHHHHHBMMMMQMMNNDDDDDDPDDDDDTPPPPPPPPPKKHHHHHHHHHWQZZZLLLLLLLGGGQQTTTTTTTTCCIICCCIIIIIIIIIKAAAAANNNNNNQQQQQQQUUUUUUUUYYYYIIIIIIIIIICCCRRR",
        "UUMUUUHHHHMMMMQMMNNNDDDDPPPPPPPTPPPPPPPKKKHHHHHHHHHHZZZZZZZLLLLGGGGGGGTGTTTTTCCCCCCIIIIIILIIIKKAAZZNNNNBNNQQQQQQUUUUUUUUYYYYIIIIIIIIIICCCRRR",
        "UKMUUMHHHHMMMMMMMMMNNPPPPRPPPPPPPPPPPPPPKKKHHHHHHHHHHZZZZLLLZLZGGGGGGGGGGGKTCCCCCCCIIIFFFKKKKKGHAZZZZNNNNNQQQQQQUUUUUUUUYYYYIIIDIIIIIICCRRRR",
        "UUMUMMHHHMMMMMMMMMMPPPPPPPPPPPPPPPPPPPPKKKHHHHHHHHHHHZZZZZLZZZZGGGGGGGGGGGGCCCCCCCIIIFFKKKQKKGGGGZZNNNNNNNQQQQQUUUUUUUUUUYYYIYYIICCCCCCCCCRR",
        "AUMMMMMMMMMMMMMMMPPPPPPPPPPPPPPPPPPPPPKKKKHHHHHHHHHHZZZZZZZZZZZOOGGGGGGGGGGCCCCCCRRFFFFKKKKKKGGGGGGNNNNNNNQQQQUUUUUUUUUYYYYYYYYYCCCCCCCCCRRR",
        "AAMMMMMMMMMMMMMMPPPPPPPPPPPPPPPPPPPPPPKKKKHHHHHHHHHHBBZZZZZZZZZZOOOOOGGRGGCCCCCRRRRFFFFFFKFGGGGGGGGNNNNNNNNQQQUUUUUUUUUYYYYYYYYYCCCCCCCCCRRR",
        "MMMMMMMMMMMMMMMMPPPPPPPPPPPPPPPPPPPPPPKKKKKHHHHHHHHBBBBZBZZZZZZOOOOOUUURRRYCCCCRRRRRFFFFFKFFGGGGGGGNNNNNNNNNQQUUUUUUUYYYYYYYYYYCCCCCCCCCCCRR",
        "FFMFFFMMMMMMMVVVPPPPPPPPPPPPPPPPPPPPPPKKKKHHHHHHHHHHBBBBBBZZZZZOOOOOUUURRRYYCCCRRRRRFFFFFFFGGGGGGNNNNNNNNNNNNNPPUUUUKKYYYYYYYYCCCCCCCCCCCRRR",
        "FFFFFFFEEOMMMMVEFFFFPPPPPPPPPPPPVVPPPKKKKKHHHHHHHHBBBBBBJZZZZZZZOOOOUURRRYYGYCCRRRRRRFFFFFFFGGGGGGGNNNNNNNNNNPPPPPUKKKKYYYYYYYYCCCCCCCCCRRRR",
        "FFFFFEEEEOMMDDEEFFFFFPPPPPPPPPVVVVPPPKKKKHHHHHHHHBBBBBBBBJZZZZZZOOOUURRYYYYYYYCCCRRRRRFFFFFFGGGGGGGNNNNNNNNNNNPPPPUKKKYYYYYYYYYCCCCCCCCCRRRR",
        "FFFEEEEEEOOMEDEEFFFUFFFFPPPPPPVVVVPPPKKKKHHHHHBBBBBBBBBBBZZZZZUUUUUUURYYYYYYYYRRRRRRRFFFFFFFVGVGGGGGNNNNNNNNNKPPPPPPKKYYYYYYYYYCCCCCCCCCCCRR",
        "FFEEEEEEEOOEEEEEFFFFFFFFPPPPIVVVVVVKKKKKKKHHHHHHHBBBBBBBBZZZUUUUUUUUUUAYYYYYYYYRRRRRRRFFFFFFVVVVGGGGGNNGNVNKNKKKPPPKKKKYYYYYYYCCCCCCCCCCRRRR",
        "FFEEEEEEEEEEEEEEFFFFFFFFPPVVVVVVRVVKKKKKHHHHHHHBGBBBBBBBBBBUUUUUUUUUUUAAADDMMDORRRRRRRRFFFFFVVVVVVVGGGNGNVVKKKKKKKPPPEYYYYYYYYYCCCCCCRRRRRRR",
        "FFEEEEEEEEEEEEEFFFFFFFFFVVVVVVVVVVVVKKKKHHHHHHHBBBBBBBBBBBBBUUUUUUUUUNUAUUDDDDDRRRRRRRRFFFFVVVVVVVVGGGNGKKKKKKKKEEEEEEEFYYYYYYCCCCCCCRRRRRRR",
        "FFFFFFEEEEEEEEFFFFFFFFFFMVVVVVVVVVVGPPPKKKKKHHHEBBBBBBBBBBBBUUUUUUUUUUUUUDDDDDXXRARRRRRRFFFVVVVVVVCCCGNGGGGGKKKEEEEEEEEEYYEYYYHHCNCNNDDDDDDR",
        "FFFFFFEEEEEEEFFFFFFFFFFFFVVVVVVVVVVVPPPPKQKHHHRBBBBBBBBBBBNUUUUUUUUUUUUUUUDDDDAXAADRRRRRFFFVVVVVVVCCCGGGGGTGKKEEEEEEEEEEEEEEHHHHNNNNNDDDDDRR",
        "FFFFFEEEEEEEEFFFFFFFFFFFFVVVVVVVVVXXXXPPPQQRRHRBBBBBBBBBBBBBUUOUUUUUUDUDDDDDDAAAAADDRRRRRFFFVVVVVVVEEGGGGGTTTVVVEEEEEEEEEEGGGHHNFNNNNNNDOORO",
        "FFFFFEEEEEEEEEEFFFFFFFFFFVVVVVVVVVXXXXQQQQQRRRRBBBBBBBBBBBBOUUOOOKUUDDDDDDDDDJAAAADDDRFFFFFVVVVVKVEEEEEEEGTTTVVEEEEEEEEEEEGGGNNNNNNNNNNNOOOO",
        "FFTFFFEEEEETEEEEFFFFFFFFFVVVVVVVXXXXXQQQQQQRHHRRRRRRBBBOOBBOUOOOOKKKKDDDDDDDDDAAADDDDDDDDDDVVVVVKEEEEEEEITTTTTVEEEEEEEEEEGGGGGGNWNNNNNNOOOOO",
        "TFTTTTEEEEEEEEEEFFFFFFFFFVVVVVVVXXXXQQQQQQQRRHHHHRRRRBOOBBOOUOOOOKKKKDDDDDDDDDDAADDDDDDDDDPVVIIVKEEEEEEEEETTTTTEEEEEEEEEEGGGGGGNNNNNDNNNOOOO",
        "TTTTTTTETEEEEEEEFFFFFFFFCCVVVVVVXGGXQQQQQQQRHHHHHVVRRBOOOBOOOOOKKKKKKDDDDDDDDDDDDDDDDDDDDDDDIIIEEEEEEEEEEEETYTTTTYEEEEEEEGGGGGGCNNNNNNRRROOO",
        "WTTTTTTTTTTTEWEMEFFFFFFFFVVGVVXXXGGXQQQQQQQHHHHHHVVVVVOOOOOOOOKKKKKJJDDDTDDDDDDDDDDDDDDDDDDIIIESEEEEEEEEEEEYYYYYYYYEEEEEEEGGGCCCCCNNNQRRROOO",
        "TTTTTTTTTEEEEEEEEFFFFFFFHGGGVVGGGGGGHQQQQQQQHHHHCVVVVVOOOOOOZOZSKKKKKKDTTDDDDDDDDDDDDDDDDDDDIEEEEEEEEEEEEEEYYYYYYYYEEEEEEEGGGCCCCCCNRRRRROOO",
        "TTTTTTTTTTTTEEEEFFFFFFFHHGGGGGGGGGGGHHQQQQQHHHHCCVVVYVVOOOOOZZZZHKKKKSSDDDDDDDDDDDDDDDDDDDDDDEEEYEEEEEEEEYYYYYYYYYYYYYECCCGGGCCYYYCCOORRROOO",
        "ITTTTTTTTTTTEEEESFFHHHHHGGGGGGGGGGGGHHHQQQHHHHVVVVVVVVVVVOZOZZZHHHHKKSSDDDDDDDDDDDDDDDDDDDDDXEEYYYYYEEHHCCYYYYYYYYYYYYRRRRGGGCYYYYYYOOOROOOO",
        "IITTTTTTTTTEEEEEEFFHPPPGGGGGGGGGGGGHHHHHHQHHHVVVVVVVVVVVVZZZZZZHHHHHKDDDDDDDDDDDDDDDDDDDDDDDDEYYYYYYYHHHCCYYYYYYYYYYYYRRRRGGGCYYYYYMMOOOOOOO",
        "ITTTTTTTTTTTEEEEEFFPPPPPGGGGGGGGGGGHHHHHHHHHHHHVVVVVVVVVZZZZZZZHZZHHHDDDDDDDDDDDDDDDDDDDDDDDDDYYYYYYYHHHHHRYYYHHHYYYYYRRRRRCCCCYYYMMMMOOOOOO",
        "IITTTTTTTTTTEEEEPPPPPPPPGGGGGGGGJJHHHHHHHHHHHHHVVVVVVVVVZZZZZZZHZZHHHDDDDDDDDDDDDDDDDDDDNDWWYYYYYYYYHHHHHHHYYYPPHHHYYYRRRRRRRRRYYYYMMMOOOOOO",
        "ITTTTTTTTTTTTTPPPPPPPPPGGGGGGGGJJJJHHHHHHHHHHHHVVVVVVVVVVZZZZZZZZHHHHHHHDDDDDDDDDDDDDDDDDWWWWYYYYHYHPHHHHHYYYYHHHYYYYYRRRRRRRRRYYYYMMMMOOOOO",
        "IITTTTTTTTTTTPPPPPPPPPDGGGGGGGGJJJJHHHHHHHBBBHVVVVVVVVVVZZZZZZZZZZHHHHWDDDDDDDDDDDDWWWWWWWWWWWYYYHHHHHHHHHHHXXHHHYYYYYRRRRRRRRRYYYNNNMNNNNNO",
        "IITTTTTTTTTTTTPPPPPPPPPLGGGGGGJJJJJJHHHHHHBBBBAVVVVVVVVVZZZZZZZZZHHHWWWWDUCDDDDDDDDXXWWWZWZZZZZYHHHHHHHHHHHHHHHHHYYYYYRRRRRRRRRYYDNNNNNNNNOO",
        "IIITTTTTTTTTTTKPPQPPLLLLGGGBJJJJJJJJJHHHHBBBBFBVVVVVVZZVZZZZZZZZZHHHWWWWICCDDDDGGGXXXXWZZZZZZZZYHHHHHHHHHHHHHHHHHYYYYYRRRRRRRRRRRRRRNNNNNGGO",
        "GGGGTTTTLTTTTTKQPQQPPLLLHHGHHJJJJJJJJJHHBBBBBBBBBVVVVZZZZZZZZZZZZWWWWWWWWWCCCCGGXXSXXXZZZZZZZZZZHHHHHHHHHHHHHHHHHHYYYYRRRRRRRRRRRRRRNNNNUUGG",
        "GGGGLLLLLLTTQQQQQQQQLLLLHHHHHJJJJJJJJJJUUSBBBBBBBVVVVZZZZZZZZZZZWWWWWWWWWCCCCGGGXXXXXXXZZZZZZZZZHQQQQHHHHHHHHHHHHYYYYYRRRRRRRRRRRRRRNNNNNNNG",
        "LGLLLLLLLLTDQQQQQQQLLLLHHHHHHJJJJJJJUUUUUUUUBBBBBBBZZZZZZZZZDZZZWWWWWWWWCCCCCCGGXXXXXXXXXZZZZZZZZQQQQQHHHHHHHHEEHYYYYAARRRRRRRRRRRRRNNNNNGGG",
        "LLLLLLLLLLLQCQQQQQQLLLLHHHHHHJJJJJJJUUUUUOUUUBBBBBBZZZZZUDDDDWWWWWWWWWWWCCCCCGGGXXXXXXXXMMMMMMQQQQQQQQQHHHHHHHHHWYYYFFARRRRRRRRRRRRRNNNGGGGG",
        "LLLLDRLLLQQQQQQQQQLLLLHHHHHHHJJJRRJJUUUUUUUUUUBBBBBBBZZVDDDDDRWWWWWWWWWWCCCCCGGGVVVXXXXXMMMMMMQQQQQQQQQHHHHHHHHHHFFFFAARRRRRRRRRRRRRNNGGGGGG",
        "LLLLRRRLLLQQQQQQQQQQLLHHHHHHHHHJRJJJUUUUUUUUUUUBBBBBBGZVDDDDWWWWWWWWWWWWCCCCGGVGVVVVXXXXMMMMMMMMMMQQQQQHQQHHHHHHHXFFFFARRRRRRRRRRRRRPNGXLGGG",
        "SRLRRRLLLLLQQQQQQQQLLLHHHHHHHHHHRRJJJUUUUUUUUUUBBBBBBBBDDDDDWWWWWWWDWWWHCCCCGGVVVVVVVXXXMMMMMMMMMMQQQQQMQUHWHHHXXXXXRRRRRRRRRRRRRNNNNNLLLLLG",
        "SRRRLLLLLLLQQQQQQQQCCHHHHHHHHHHHHJJUUUUUUUUUUUBBBBBBBBDDDDDDWDDWDDDDDWWDFFFGGGVVVVVVVXXXMMMMMMMMMMQQQQQQQXGXXXXXXXXXRRRRRRRRRRRRRNNNNNLUULLG",
        "SRRLLLLNLQQQQQQQQCCCCCHHHHHHHHHHQUUUUUUUUUUUUUBBBBBBWWDDDDDDDDDDDGDDDWDDFFGGGGVVVVVVXXXXMMMMMMMMMMQQQFQQQXXXXXXXXXXFRRRRRRRRRRRRRNNNLLLLLLLL",
        "SLLLLLLNLQQQQQQQQQQCCHHHHHHHPHHHHUUUUUUUUUUUUUBBBBBBBWWWDDDDGDGGDGDDDDDDDDQQGGKVVVVVXMMMMMMMMMMMMMQQQQQQQQQXXXXXXXXFRRRRRRRRRRROOOJNLLLLLLLL",
        "SNLLLLLNNQQQQQQQQQQCHHHHHHHHHHHHCUUUUUUUUUUUUZBBBBBBWWWWWWDDGDTGGGGGDDDDDDQQGGGPPGVVVMMMMMMMMMMMMMQQQQQQQQXXXXXXXXFFRRRRRRRRRROOOOJJLLLLLLLL",
        "SNNNNNNNNSQQBQQQQQQXHHHHHHBHHBBBUUUUUUUUUUUUZZZZBBWWWWWWWWWWGGGGGGGGDDDDDDQQQGGGGGGCMMMMMMMMMMMMMMZZQQQQQQXXXXXXXXXERRRRRRRRRRRRROJFFBLLLLLL",
        "GKNNRNNNNNNBBQQQQQXXHHHHHHBBBBBBBBUUUUUUUPPPZZZZBBBWWWWWWWWWWGGGGGGYGDDQDQQQGGGGGGGGMMMMMMMMMMMMMMQQQQQQQQQXXXXXXXEERRRRRRRRRRRRRFFFFFLLLLLL",
        "GNNNNNNNNNBBBQQQQBBXHHFFBBBBBBBBBBBBUUUUUPPPPPPPBBBBWWWWWWWWWGGGGGGGGDDQQQQGGGGGGGGGMMMMMMMMMMMMMMQQQQQQQQQXXXXXXXEERRRRRRRRRRRRRFFFFLLLLLLL",
        "GNNNNNNNNNBBBBQQBBBXXFFFBBBBBBBBBBBUUUUUPPPPPPPPBBBMMMWWWWWWWGGGGGGGDDDQQQQGGGGGGGGGMMMMMMMMMMMMMMQQQQQQQQQXXXXXQXEERRRRRRRRRRRRRFFFFXLLELLL",
        "GGYNNNNNNNNBBBQBBBBBBFFFBBBBBBBBBBUUUUPPPPPPPPPPPBBWWWWWWWGWWGGGGGGGGGGGQQQGGGGGGGGCMMMMMMMMBBBZQQQQQQQQQQQQXXCXXXXERRRRRRRRRRRRRFFFFFEEELLL",
        "GGYYNNNNNNNBBBBBBBBBFFFFFBBBFBBBBBBBUUPPPPPPPPPPPBBWWWWWWWGGGGGGGGGGGGGGGQQQQGGGGGGCMMMMMMMMBBBMMQQQQQQQQEEXXEEZEEEEEEEEEEEEFRRRRFFFFFEEEELL",
        "GGGGNNNNNNNBBBBBBBBFFFFFFBFFFBBBBBBBBPPPPPPPPPPPPPBWWWWWWWWGGGGGGGGGGGGQQQQGGGGGGGSSMMMMMMMMBBBMMQQQQEEQEEEXEEEEEEEEEEEEEEEEERRRRFFFFEEEEEEL",
        "GGGGNNNNNNNBBBBBBBBFFFFFFFFFBBBOOBBBBPPPPPPPPPPPPPPWWWWWWWWGGGGGGGGGGGGGQQQQQQQGGSSSMMMMMMMMBBBMMQQQQEEEEEEEEEEEEEEEEEEEEEEEERRRRFFFFEEEEEEE",
        "GGGGGNNNGGBBBBBBBBBFFFFFFFFFFOOOBBBOPPPPPPPPPPPPPWWWWWWWWWWWWGGGGGGGGGGQQQQSQSQSSSSSMMMMMMMMBBBQQQQQQQEEEEEEEEEEEEEEEEEEEEEEERRRRFFFEEEEEEEP",
        "GGGGGGGGGGGGBBBBBBBBFFFFFFFFFFOOOOOPPPPPPPPPPPPPAAAAWWWWWWWWWWWWGGGGGGQQQQQSSSSSSSSSSMMMMMMMBBBQQQQQQEEEEEEEEEEEEEEEEEEEYEEEERRRREEEEEEEEECI",
        "GGGGGGGGGGGGBBBBBBBBFFFFFFFFOOOOOOOPPPPPPPPPPPPAAAAAWWWWWWWWWWWWGWGGQQQQQQQQSSSSSSSSSMMMMMMMBBBUUQQQEEEEEEEEEEEEEEEEEEEEYBEEEEEEEEEFEEEERIII",
        "GGGGGGGGGGGGBBBBBBBBBBFFFFFFOEOOOOOPPPPPPPPPPPPAAAAAWWWWWWWWWWWWWWGGGGQQQQQSSSSSSSSSSSSMBBBSBBBUUUUQEEEEEEEEEEEEEBBBEEEEEBEJEGGEEEEFFEEERIII",
        "GGGGGGGGGGGGBBBBBBBBBBBBBFFFFEEOOOOPPPPPPPPPPPWAAAAAAWWWWWWWWWWWWWWUGGQQQQQSSSSSSSSUUUYBBBBUBBBUUUUUNEUUEEEEEEEEEBBBVEBEBBBJJJGEEEGFFERRRIII",
        "GGGGGGGGGGGGGGBBBBBBBBOOOFFFIOOOOOOPPPPPPPPPPWWWWAATTTWWWWWWWWWWWWWWQQQQQQQQSQSSSSUUUUYTBBBBBBBUUUUUUUUZEEEEEEEEEBBBBEBBBBBJJJGEEGGFFERRRIII",
        "GGGGGGGGGGGGGBBBBBBBBBBOOBOOOOOOOOOPPPPPPOKKHKKKHHHTHTTZZWWWWWWWWWWQQOQQQQQQQQQQSQUUUUYYBBBBUUUUUUUUZZZZEEEEEEEEEEEBBBBBBBBGGGGGGGGGGERRRIII",
        "GGGGGGGGGGGGGBBBBBBBBBBBOOOOOOOOOOOPPPPPPKKKKKKKHHHHHHHBZZZZWWWEWWOOOOOQQQQQQQQQQQUYYYYYBBBBUUUUUUUUUZZZEEEEEEEEEEEEBBBBGGPGGGGGGGGGDERRRIII",
        "GGGGGGGGGGGXXBBBBBBBBBBBOOOOOOOOOOOPPPPPPKKKKKKHHHHHHHZZZZFWWWWWWWOOOQQQQQQQQUUUUUUFYYYYYYYUUUUUUUUUZZZZEEEEEEIEBBBBBBBBBGGGGGGGGGGGGRRRRIII",
        "GGGGGGGGGGXXXBBBBBBBBBBBBOOOOOOOOOOPPPPPPKKKKKHHHHHHHHHHZZZWWWWWWOOOQQQQQQQQQUUUUUUUYYYYYYYYYGUUUUZZZZZZZZEMMMEEBBBBBBBBBGGGGGGGGGGGGRRRRIRR",
        "GGGGGGGGGGXGGBBBBBBBBBBBOOOWOOOOOOOOKKKKKKKKKKHHHHHHHHHHMMMWWMWWOOOOOQQQQQQQQQUUUUUUZZZYYYYYYZUZZZZZDZZDDDMMMMMMBBBBBBBBBGGGGGGGGGGGGGRGRRRR",
        "GGGGAAGGGGGGGGBBBBBBBBBBOOWWOOOOOOOOOOKKKKKKKKKKHHHHHHHHMMMMWMWWWOOOOOQQQQQQUUUUUUZZZZZZZYYZZZZZZZZZDDDDDMMMMMBBBBBBBBBBBKGGGGGGGGGGGGGGGRRR",
        "GGGGGGGGGGGGGBBBBBBBBBBBWWWWOOOOOUOOKKKKKKKKKKKHHHHHHHHHMMMMWMMMOOOOOOOOOQUUUUUUUUUZZZZZZZZZZZZZZZZZDDDDDMMMSSSSBSBBBBBBKKKKGGGGGGGGGGGGGRRR",
        "GGGGGGGGGGGGGGBBBBBBBBBBBBWWWUUUOUOVVUUUKKKKKKHHHHHHHHHHHMMMMMMMOOOOOOOOOQUUUUUUUUUUUEZZZZZZZZZZZZDDDDDDDDMSSSSSSSBBBBBBKKKKGGGGGGGFFFGGGRRR",
        "GGGGGGGGGGGGGGBBBBBBBBBBBBPWWPPUUUUUUUUUKKKKKKKKHHHHHHHQMMMMMMMMMMMMLOLLOONUUUUUUUUUUEZZZZZZZZZZZDDDDDDDDDMSSSSSSSBBBKBKKKKKKKGGGGGFFFGGGGRR",
        "GGGGGGGGGGGGGGBBBBBBBBBBBBPPPPPUUUUUUUUUKKKKKKKKKHHQPPPQMMMMMMMMMMMLLLLLNNNNUUUUUUUUUEZZZZZZZZZZZZZDDDDDDDDSSSSSSSSXKKKKKKKKKKGGGGGFFFGGGGGR",
        "GGGGGGGGGGGGGGBBBBBBBBBBBBPPPPPUUUUUUUUUKKKKKKKQKSQQPQPQQMMMMMMMMMMLLLNNNNNNNUUUUUUUUUZZZZZZZZZZZZYDDDDDDDSSSSSSSSSSSYYKKKKKKKKKGGGFFFGGRRRR",
        "GGGGGGGGGGGGGBBBZBBBBBBPPPPPUPUUUUUUUUUUKKKKKKKQQQQQQQPQQMMMMZZZZMMLLLLNNNNNNUUUUUUSUUZZZZZZZZZZZZYYADDDANNSSSSSSSSJKYKKKKKKKKKKGGGFFFGGZRRR",
        "GGGGGGGGGGGGGGBBZBBBBBBBUUPUUUUUUUUUUUUUUKKKKKKQQQQQQQQQQMZZZZZMMMZZLLZZZNNNUUUUUUUUUZZZZZZZZZZZZZZYAADAANNSSSSSSSSJKYYKKKKKKKKKZZZFFFQZZRRR",
        "GGGGIGGGBBBBBBBBZZBBBBBBUUUUUUUUUUUVUVKKKKKKKKQQQQQQQQQQQQZZZZZZMZZZLLZZZNNUUUUUURDDUUZZZZZZZZZZZYYYYAAAANNNNSSSSSSSKKKKKKKKKKKZZZZFFFFFFFFR",
        "GGGGGGGNNBBBBBBZZBBBBZBZZUUUUUUUUUVVVVKKKKKKKKQQQQQQQQQQQZZZZZZZZZZZZZZZZZNNUUDUUUDDZZZZZZZZZZZZZYYYYYAANNNNNNNNOSRRRKKKKKKKOKKKPZZFFFFFFFFR",
        "GGNNNGGNNNNNBBZZZBBBBZZJZZZUUUUUUUUVVVVVKMMMKKQQQQQQQQTTQTTTZZZZZZZZZZZZZZZDDDDUUUDDDZZZZZZZBZZZZYYYYAANNNNNNNNNNRRRRKKKKYKKKKKPPZNFFFFFFFFR",
        "NNNNNGNNNNNNBBBZZZBBBZZZZZZZUUUUUVVVVVVVVVMMKKQQQQQQQQTTTTTLLZZZZZZZZZZZMMMMLDDDDDDDDZYBBBBBBZZZZYYYYAANNNNNNNNRRRRRKKKKKKKKKKPPPZZFFFZZZZRR",
        "NNNNNNNNNNNJBBZZZZZZZZZZZZUUUUUUUVVVVVVVVMMMMKUUQQQFFTTTTTTTTZZZZZZZZZZZMLLMLDDDDDDDDDBBBNBBBBZYYYYYYAAANNNNNNNNNNNNKKKKKKKKKKPPPZKZZZZZZRRR",
        "NNNNNNNNNNNNBBZZZZZZZZZZZZUUUUUUUVVVVVVMVMMMMUUUUTTTTTTTTTTTTTZZZZZZZZBBLLLMLDDDDBDDBBBBBBBBBBBYYYYYYYYYNNNNNNNNGGGKKKKKKKKKPPPPPPZZZZZZZIRR",
        "NNNNNNNNNNNQZZZZZZZZZZZZMUUUUUUUUVVVVVVVUMMMMMUUTTTTTTTTTTTTTZZZZZZZZZZBBLLLLDDDDBBBBBBBBBBBBBBYYYYYYYYYNNNNGGGGGGGKRKAAAKKPPSPPPPZZIZZIIIIR",
        "NNNNNNNQQQQQQZZZZZZZZZZZMMUUUUUUUUVVVVVVUMMMMUUUTTTTTTTTTTTTTZZZZZZZZZZBBLLLLLDLDBBBBBBBBBBBBBBYVVVYYYYYNNNNGGGGGZGZRSSSSSSSSSPPPPPPZZIIIIII",
        "NNNNNNNNQQOQJZZZZZZZZZMMMMMUUUUUUCVVVDDVUMMMUUUUTTTTTTTTTTTTTTZZZZZZZZZBBLLLLLLLVVVVBBBBBBBBBBVVVVVVYYYYVVGGGGGGGZZZZSSSSSSSSSSPPPPPZZIIIIID",
        "NNNNNNNNNOOQJJJZZJZZZMMMMMMMUUUMUCCCSSSSSSSUUUUUTTTTTTTTTTTTTZZZZZZZZZZBLLLLLLLLVVVVBBBBBBBBBBVVVVVVVYYYVVVGGGGZZZZZZSSSSSSSSSSSSPPPPPIIIIII",
        "NNNNNNNOOOAJJJJJJJJZZMMMMMMMMUMMUCCCSSSSSSSUUUUUTTTTTTTTTTTTTTTZZZZZZPZLLLLLLLLLVVVVVBBBBBBBBBBVVVVVVVVVVVVGGGGGGZZZSSZSSUSSSSSSSSSWWPIIIIII",
        "NNNNNNNOOOJJJJJJJJJZZMMMMMMMMMMMUCCCSSSSSSSUUUUUTTTTTTTTTTTTTTTCZZZZZZLLLLLLKLLVVVVVVBBBBBBBBBVVVVVVVVVVVVVGGGGZZZZZSSZSQUSSSSSSSSWWWIIIIIII",
        "NNNNNNNNOJJJJJJJJMMMMMMMMMMMMMMMMCOOSSSSSSSUUUUUUUUUTTTTWTTTTTTCCCZRCZAAALLLKVVVVVVVBBBBBBBBABVVVVVVVVVVVVGGGZZZZZZZSSZSZUSUHSSUSSSWWIIIIIII",
        "NNNNNNNJJJJJJJJJJJJMMMMMMMMMMMMMOOOOSSSSSSSUUUUUUKUUTTTTTTTTTTTCCCCCCAAAAALKKKVVVVVVVVBBBBBBBVVVVVVVVVVVVVVVVZZZZZZZZZZZZUUUSSSSWWWWWWJJIIII",
        "NNNNNNNNIJJJJJJJJJMMMMMMMMMMMMMMMMSSSSSSSSSUUKKKKKKUTTTZZTTTTTTTCCCCCCCAANNKKKVVVVVVVVVVBBBBVVVVVVVVVVVVVVVTVZZZZZZZZZZZUUUUWWSWWWWWWIWWWIWI",
        "NNNNNNNIIJJJJJJJJJJMMMKMMMMMMMMMMMSSSSSSSSSUUUUKKKKKKZZZZZZCECTCCCCCCCLNNNNNNNNNVVVVVVVVVVBVVVVVVVVVVVVVVVVVVZZZZZZZZZZZUUUUWWWWWWWWWIWWWWWW",
        "NNNNNNNIIJJJJJJJJJJMMMMMMMMMMMMMMMSSSSSSSSSLKUKKKKKKKZZZZZZCCCCCCCCCCCCDNNNNNNVVVVVVVVVVVVVVVVVVVVVVVVVVOOOVOOOZZZZZZZZUUUUUUWWWWWWWWWWWWWWW",
        "NNNNNNIIIIJLJJJJJJMMMMMMMMMMMMMMMMSSSSSSSSSSSKKKKKKKKKZZZZZZCCCCCCCCCCCNNNNNNNVVVVVVVVVVVVVVVVVVVVVOOVVVOOOOOOOZZZZZZZUUUUUUUUUWWWWWWWWWWWWW",
        "NNNNHHUIULLLJJJJJJMMMMMMMMMMMMMMMSSSSSSSSSSSSDKKKKKKKKZZZZZZZCCCCCCCCCCCNNNNVNVVVVVVVVVVVVVVZVOOOOOOVVVVOOOOOOOZZZZUUUUUUUUUUUUUWWWWWWWWWWWW",
        "NNNUUUUUULLLLJJJJJMMMMMMMMMMMMMMMMSSSSSSSSSSSKKKKKKKKKKZZZZWWWCCCCCCCCCCCDNVVVVXXVVVVVVVVVIIIIOOOOOOVVVDOOOOOOOZZZZUUUUUUUUUUNNNNNNWWWWWWWWW",
        "LLLUUUUULLLLJJJJMMMMMMMMMZZZZMMMZMSSSSSSSSSSSLKKKKKYKKZZZZZWWWWCCCCCCCCCEDVVVVVXXIIIVVVVVVZIIIOOOOOOVVVOOOOOOOOOOOOUUUUUUUUUUUNNNNNWWMWWWWWW",
        "LLJUUUUULLLLLLJJJJMMMMMMMMZZZZZZZZSSSSSSLLLLLLLLKKAKKKKWZWWWWWWCCCCCCCCEEEEVVVVXXVIIIVVVIVIIIIIOOOOOVVOOOOOOOOOOOOOOUUUUUUUUUNNNNNWWWWWWWWWW",
        "LLLLULUULLLLLLLZZZMMMEMMMOZZZZZZZZSSSSSLLLLLLLLLLKKCKKWWWWWWWWWWWWCCEEEEEEVVVVXXXVIIIIIIIIIIIIIIOOOOOOOOOOOOOOOOOOOOUUUUUUUUNNNNNNNNWWWWWWWW",
        "LLLLULLLLLLLLLLLZEEMMEEMOOZZZZZZZZSSSSSLLLLLLLLCCCCCCKWWWWWWWWWWEEEEEEEEENNVZVJXXXIIIIIIIIIIIIIIIOOOOOOOOOOOOOOYYOOUUUUUUUUUNNNNNNNNWWWWWWWW",
        "LLLLLLLLLLLLLLLLZEEEEEEMOOZZZZZZZZZSSSSLLLLLLLLLLCCCKKWWWWWWWWWWEEEEEEEEENNXXXXXXXIIIIIIIIIIIIIIIOOOOOOOOOOOOYYYYUUUUUYYUUUUUUNNNNNZZWWWWWWW",
        "LLLLLLLLLLLLLLLLEEEEEEEMOZZZZZZZZZZZZZZLLLLLLLLLLCCCWWWWWWWWWWWWEEEEEEEEELLLLVXXVXIIIIIIIIIIIIIIIIOOOOOOOOOOOYYYYUUUYUYYUGUUNNNNNNNZZWWWWWWW",
        "LLLLLLLLLDLLLLMMEOOOEEEOOOZZZZZZZZZZZZLLLLLLLLLLLCCCCCWWWWWWWWWWEEEEEEEEEVLLLVVVVCCCIIIIIIIIIIIIIIOOOOOOOOYIYYYYYYYYYUYYYNNNNNNNNZZZZZWWWWWL",
        "LLLLLLLLLLLLMMMMVOVOEOOOOOZZZZZZZZZZZZLLLLLLLLLLLCCCCCWWWWWWWWWEEEEEEEEEVVLLLLLLCCCCCCIIIIIIIIIIIIOOOOOOOOIIYYYYYYYYYYYYYNNNNNNNNZZZZZZWWWWL",
        "LLLLLLLLLLLLMMMMVVVOEOOOOOOZZZZZZZZZZWLLLLLLLLLLCCCCCCCWPPWWWWWEEEEEEEEEEVLLLLLLCCCSPCIIIIIIDIIIIIIOOOOOOOIIYYYYYYYYYYYYNNNNNNNNNNZZZZZZZZWL",
        "LLLLLLLLLLLMMMVVVOOOOOGGGGGGZZZZZZZZZZLLLLLLLLLLLUUUCCCPPPPWWWWWEEEEEEEEELLLLLLLCSSSZZZZZZZZZZZIIIIIOOOOOZZIIYYYYYYYYYYYYYYNNNNNNNZZZZZZZZWL",
        "LLLLLLLLLLLMMVVVVVOGGGGGGGGGZZZZZZZOOULLLSLLLLUUUUUUCCCPPPPPPPWWPEEEEEEELLLLLLLLSSSSZZZZZZZZZZZDIIIOOOOOOZZIIIYYYYYYYYYYYYNNNNNNNNZZZZZZZZZL",
        "RRTTLLLLKKLVVVVVVVVWGGGGGGGGZZZZZZZZZUULUULLLLUUUUUCCCCPPPPPPPPPPEEERELELLLLLLLLLSSSZZZZZZZZZZZDIIIOOOOIIIIIIIIIYYYYYYYYYNNNNNNNNZZZZZZZZZZL",
        "RTTTALLLKKLVVVVVVVVVGGGGGGGZZZZZZZZUQUUUUULUUUUUUUUUCCCPPPPPPPPHPPEEEULLLLLLLLLLLSSSZZZZZZZZZZZDXXOOOIIIIIIIIIIIYYYYYYYYYNNYNNNNNNNQZQZOFFPF",
        "TTTTTLLLKKVVVVVVVVVGGGGGGGGGEEEZZZLUUUUUUUUUUUUUUUUUUCCCPPPPXPZHPGEUUULLLLLLLLLLLSSSZZZZZZZZZZZDDXXOXXXIIIIIIIIIYYYYYYYYYYYYQSSSNQQQQQQFFFFF",
        "TTKTTTTTKKKVVVVVVVVGGGGGGGGEEEEEEZEEUUUUUUUUUUUUUUUUUCCCOPPXXPPHHHHHUULLLLLLLLLLSSSSZZZZZZZZZZZDDXXXXXIIIIIIIIIIYYYYYYYYYYYYYSSQQQQQQQQFFFFF",
        "TTTTTTTTNNKVVVVVVVVGGGGGGGGGEEEEEEEEUUUUCCCCCCCCUUUUUCCOOOPXXHHHHHHKKLLLLLLLLLLLLSSSZZZZZZZZZZZDXXXXXRAAIIIIIIPIYYYYYYYYYYIIIMSMQQQQQQQFFNFF",
        "TTTTTTTNNNKSVVVVVVVGGGGGGGGHHHHHHHEEUUUUCCCCCCCCUUWCCCCCOOOOXXXHHHGKKKKLULLLLALLLSSZZZZZZZZZZZZDDXRXXRAAAIIIIIIIYYYYYYYYIIIIIMMMQQQQQQQQFFFF",
        "TTTTTTTTNNKSSVVSSVGGGGGGGGGHHHHHHHEECCCCCCCCCCCCUUWWCCCCOXOXXXXXXKKKKKKLLLOLLAALSSSZZZZZZZZZZZZDXXRRRRPAAIIIIIIIMMMYYYYYIMMIIMMMQQQQQQQFFFFF",
        "TTTTTTTTRRSSSBVSVVGGGGGGGGGHHHHHHHEUCCCCCCCCCCCCKWWWWWWWOOOXXXXXXKKKKKKKLLLHLAAASSSZZZZZZZZZZZZDDDRRRRPPPFIIIIIIMMMMYYIIIMMMMMMMMQQQQBFFFFFF",
        "TTTTTTTTRTSSSSSSVGGGGGGGGHHHHHHHHHEVCCCCCCCCCCCCNNWWWWWWWWWWXXXKKRKKKKKKKLLLLLAAASSZZZZZZZZDDDDDDRRRRPPPPPPIIIIIMMMMMIIMMMMMMMMMMQQQQBFBBBFF",
        "TTTTTTTTRTSSSSSSSLLLGGGGGHHHHHHHHHEVCCCCCCCCCCCCNNWWWWWWWWWSXXXKKKKKKKKKKLLLLLAAAASZZZZZZZZDDDDDDRRRRRPPPPPRRRIMMMMMIIIIMMMMMMMMMQQQBBBBBBFF",
        "TTTTTTTTTTSSSSSSPLLLLGGGLHHHHHHHHHAVVVVVVCCCCCCCNNNNWWWWWWSSXXXKKKKKKKKKKKLLAAAAAGGZZZZZZZZQQDRRDDRRRPPPRRRRRRMMMMMMMIIIMMMMMVVVVVVVVVVBFFFF",
        "TTTTTTTTTTSSSSSSSLLLLLLLLHHHHHHHHHAVVVVVVCCCCCCCNNNNNNWWWWSXXXXXKKKKKKKKKKLKKKKKAAGGGGGGQQQQQQRRRRRRRRRPRRRRRMMMMMMMMIIIMMMMMVVVVVVVVVVBRRRR",
        "TTTTTTTTTTSSSSSSLLLLLLLLLHHHHHHHHHVVVVVVVVVNNNNNNNNNNNNWWWSSXXXXSKKKKKKKKKKKKKKAAAGGGGGSSQQQQQQTRRRRRRRRRSSRRSNMMMMMMIIIMMMMMVVVVVVVVVVBRRRR",
        "LLLLTTTTCCCCSSSSLLLLLLLLLHHHHHHHHHDVVVVVVVVNNNNNNNNNNNNNNSSSSSSSSKKKKKKKKKKKKKKKAAGSSSGSSQQQQQTTRRRRRSSSSSSRRSSMMMMMMIIIMMMMVVVVVVVVVVVBBRRR",
        "LLLLLTTTTTSSSSSSLJLLLLLLLHHHHHHHHHDVVVVVVVVVNNNNNNNNNNNNSSSSSSSSSSSKKKDDKKKKKKKKKKSSSSSSSSQQQTTTRTTTTTSSSSSSSSSMMMMMMVVIMMMPVVVVVVVVVVVBBRRR",
        "LLLLLTTTTLSSSSRJJJJLLLLLLHHHHHHHHHDVXVVVVVVVFFNNNNNNNNNSSSSSSSSSSSKKKKDDKKKKKKKKKKSSSSSSSSQQTTTTTTTTTUSSSSSSSSSMMMMMMVVVMMMMVVVVVVVVVAAAURRR",
        "LLLLLLLLLLLLSJJJJRLLLLLZZHHHHHHHHHFFVVVVVVVVFFFFFFNNNNNSSSSSSSSSSSSSKDDDDDKKSSKSSKSSLSSSSQQTTTTTTTTTTUUUUSSSSSVVVVVVVVVVMMMSVVVVVYYYYARRRRRR",
        "LLLLLLLLLLKKKJJJJRLLHHHHHHHHHHHHHHFFDMVVVVVQQFFFFFFNNNNSSSSSSSSSSSSSSSSMDDDDSSSSSSSSLSSLSQTTTTTTTTTTTUUUSSSSSSVVVVVVVVVVVMMJJJJYYYYYYAARRRRR",
        "MLLLLLLLLLKKKJJJJJRLHHHHHHEDDDDDDDDDDMMVVVVQFFFFFFFFNNSSSSSSSSSSSSSSSSSMDDSSSSSSSSSSLLSLLQTTTTTTTTTEIIISSSSSSSSMVVVVVVVVJJMJJJYYYYAAAAAAAAVV",
        "MLLLLLLLLLKJJJJJJJJRHHHHHHDDDDDDDDDDDDDDQQQQFFFFFFNNNFFMSSSSSSSSSSSSSSSDDDDDSSSSSSSLLLLLVTJTTTTTTTTEIIIISSSSSSSSVVVVVVVJJJJJJJJJYYAAAAAAAAAA",
        "MMMLLLLLLLLJJJJJJJRREEEEEELDDDDDDDDDDDDDQQQQFFFFFFFFFFFSSSWWWWSSSSSSSSSFDDDSSSSSSSLLLLLLTTTTTTTTTTTEIIISSGGGWMMHMMMVVVVJJJJJJJJJJJJAAAAAAAAA",
        "RMRLLLLLLLLJJJJJJRRREEEEEEDDDDDDDDDDDDDQQQQQFFFFFFFFFFFFSLWWWSSSSSSSSSFFFDDSSSSSSSSSLLLLLLTTTTTTTTEEIIIIGBGGGGMMMMMMMVJJJJJJJJJJJJAAAAAAAAAU",
        "RRRBBLLLRRRJJJJJRRRREEEEEEEDDDDDDDDDDDDQQQQQQFFFFFFFFFFFSLLWWWSSSSSSFFFFDDNSSSSSSSSSLLLGLMMTKTTTTTEEIIIIGBBGGGGMMMMJJJJJJJJJJJJJJJAASAAAAAAU",
        "RRRRLLLLRRJJJJJRRREEEEEEEEEDDDDDDDDDDDQQQQQQFFFFFFFFFFFFSLLLLLSSSSFFFFFNNNNNNSSSSSSSSLLLLMMTTTTTTTTTIIIGGGGGGGGGGGGGZJJJJAAJJJJJJAAAAAAAAAUU",
        "RRRRRRRRRRRRJJJRRREEEEEEEEEDDDDDDEDDDQQQQQQQFFFFFFFFFFFLLLLLFFSSSSSFFFNNNNNNNSNSSSSSSLLLMMMIIIIITPTTIIIGGGGGGGGGGGGGOIIJJAAAAAAAAAAAAAAAAAUU",
        "RRRRRRRRRRRRRJRRRRREEEEEEEDDDDDEEEEDQQQQQQQQFFFFFFFFFFFLLLLLFFSSSFFFFFNNNNNNWNNNSSSSSMMMMMMIIIIPPPTIIIGGGGGGGGGGGGGGOOOJOAAAWWWWAAAAAAAAAUUU",
        "RRRRRRRRRRRRRRRRRRREEEEEEEDDDEDEEEQQQQQEQQQQSSFFFFFFFFFLFLLLFFFSSFFFNNNNNNNNNNNNSMMMSMMMMMMIIIIIPIIIIIGIIIGGGGGGGGGGOOOOOOAAAAWAAAAAAAAAAUUU",
        "RRRRRRRRRRRRRRRRRRRRRREEEEEEEEEEEEQQQQEEQQQSSFFFFFFFFFDFFFLLLLFFFFFFNNNNNNNNNMMNMMMMSMMMMMIIIIIIPIIIIIIIIIGGGGGGGGGGGOOOOZANNWWWWAAAAAUUUUUU",
        "RRRRRRRRRRRRRRRRRRRRRRREEEEEEEEEEEEEEEEEQSSSFFFFFFFFFFFFFFFLLFFFFPPPNNNNNNMNMMMMMMMMMMMMMMMIIIIIIIIIIIIIIIGGGGGGGGGGGOZZZZZNNWWWWAAAAUUUUUUU",
        "RRRRRRRRRRRRRRRRRRRRRRREEEEEEEEEEEEEEEEQQSSSSSSSSFFFFFXFFNNNLFFFFPPPNNBBNMMMMMMMMMMMMMMMMMMIIIIIIIIIIIIIIIIIQGGGGGGGGZZZZZZNWWWWWWAUUUUUUUUU",
    }; // clang-format on
}
}  // namespace aoc2024::day12