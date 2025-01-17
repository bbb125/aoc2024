#pragma once

#include <string>
#include <vector>

namespace aoc2024::day4
{
inline auto input()
{
    std::vector<std::string> data{
        //
        "MXXMASAMXSAMXSXMAMXXAMXASAXASMSMXAAMAMXXMMXAMXSXMAMSAMSAMMXASXXXXMXSXM"
        "SMSXSMSMMSSMMXSAMXSSSSXXXMMSSSMMXMAMXAXAMXMSMSSSMMSASMXSXAAXMSSMXXXSX"
        "S",
        "SASAMXSAMAMXAAAMSMSSMSAMXMAMAAAMSSMMSMXXMAXSAMXMMAAAAASASMXSXAMSMSAAXX"
        "MASASAMXXAAAXAXXMAXMAMAMSAMXAAMMSXXASMSMAMXAASXXAXSAXAASXSXMXAAAMMMMA"
        "A",
        "MASXSXAMMSXMSMMMMAMAASASMAAAMXMMXAMAAAASMAXMAMAMSASMMMMAAAMMMXMAAMMXMS"
        "MAMAMAMMMSSMMAMMMSSMAMAMSAMMXMAAAASXSXAMAMMMSMASMMMMMMMSAMXAMSSMXAAMX"
        "M",
        "MXMAMMMMAXAMMAAAMAMMMMAMASMXMXXXSAMSSMMMMMMMAMMMAAMXSSMSMAMXAMSMSMSAAA"
        "MAXXAMXXAMAMXMXAAMAXXSAMXAMXAXMMXXSASAMSXSASAMMMMAAAXMAMAMAXMAMASXXSA"
        "S",
        "SXMXMAXMASAMSSMMSAMMAMAMXXMASAMXMXMXAAXAAMMSAMXMXSMSMSAAXAXMXMASAAMMSM"
        "SAMXXAXMMSAMSMSAMSAMXXMSSSMSMSASXMMXMAMAXMMXASMAASXSMXAMAMMXMASAMMXMM"
        "M",
        "MMMAXMXMAMAMXMAXSXMXAXXXSMSAMAAMSAMXSASMMSASXSASXMXXAMXMMMSMSSXSMMMXMX"
        "MASMSMSAMSXMAAXAXMAXSSMAXAAAASAMMAMAMMMSSSSSXMMSXMMMASMSMSAASAMAXXAMA"
        "S",
        "XASMSMSMSSMMAXSXMMMSSMSAXAMMSMMXSASAMMXMAMMSAMASAXMMXMXSAAAAXMASAMSASA"
        "MSMAAXAXXXMSMSMSMSXMMAMSSMMMXMAMSASXSXAXXAAMXMMMASMMMMXAAMMMMAXSMMASA"
        "S",
        "MMAMAMSAXXXSXSMMSMMAAAMAMSAXAAXASMMMMAAMAMXMAMSMMMASMMASMSMSMMMMAMSASM"
        "SAMMMMMMSMAXAXAMXMMXSAMAAMXMASAMXAMXAMXSMMMMSMXSAMMAAAMSMSXSSSMXASXMA"
        "S",
        "XMAMMSMMMMMMMSMAAAMMSMMXMXASXSMAXXAAMSMSASAMMMMASXMXXXAXAAAXXSAMXMMAMX"
        "SAXXASXAAMSMMMXSAMAASAMMSSSSMSSXMAMMSMSXMASXAAAMAXSSMMAAXMAAAAXXXASMA"
        "M",
        "ASXMSAXAAAMAAMMSXSMAMMMAXMASAMMSMMMSMXAMASXSMASAMMSMSMASMMXSAMXXAXMAMA"
        "XAMXMSMSXMMAXMASASXXMAMXXXMAMXASMMMAMMXAXXSSMMSSSMMXSASMSMMMSMMSSMAMA"
        "S",
        "MAMXSASXXSSSXXAMXXMASASMSMXXAMXAAAAXAMAMAMAXMAMAMMAAXMAXAAXMAMSSMMSASX"
        "SSXSAXAXMXXSMMMSXMASMAMXMMSMMMMAXAMXMSSMMMXMXMAAAAXAMXMSMXSAMXXAMXMSA"
        "S",
        "AXSAMXMXSMMASMAMXXMASXMXXXMSSMSSSMSMASMMMSMSMASAMSMSMSMSMMMMSMAAAXAMXA"
        "XAAMMMMSMSXMASXSXMAMMAXASAAXASXMSXSMMAAAXMASAMMSMMMMSAMASXMXXXMMSSXMA"
        "S",
        "MXSAMXMXAAMAMMAMMMMMSXSXMAMAMAMAXAXXAMXXAMXMXASXXAMAXAAAXAXMXMMXMSXSMM"
        "MMMMMASAAXAXXMXMXMAXAXSASXMXAXAXMMSAMSSMASMSASMAAXMASXSASMMSMXMXAMXMA"
        "M",
        "XAMAMAAXMSMSSSSMSAASMAMXMAMASXMSMMMMMSSSXSASMXXXXSSSSMSMSMMSAMXSAMXXAA"
        "AXAASMSMSMSMMSAMMSXSMMAXMAASXSMMSASAMAMMXXXSXMXSSMXMSAMXSAAXMAXMMMSMA"
        "M",
        "MMSAXMSMXMAXMXMASXSMMSMMMAXAMAAXMAAAXXAAASASXMMSXMAMXAMMXAAMAMAAAXSXXA"
        "XXMXMXMXAAXAASASAMMMXAAAMXMMAAMAMXSSMXSSSMMMMSAMXMAAMMMMSMMSSXSXSASAS"
        "X",
        "XMAMAAAXAMMMMAMMMMXASAMAXSSSSMMMSSSSSMMMMMMMXMAXAMXMMMMMXMSSSMSSXSMMSS"
        "SMSASASXMSMMMMXMAXMMAXSMSAXMSMMXSAMXXXSAMXAAAMASASMSMXMASAMXXXAXMASAX"
        "A",
        "MMAMMXMXMSSMSMSMAMXXMAMSMMAAMMMAXAAXMXXAXAXASMMSSMAXASAMMXAAAAXXMSAAAX"
        "AASXSASMMMAMXXSSSMAMSMXXSXSMMXXMMMXMSMMXMXSSMMAMXMXAMXAMXAMAMMMMMAMMM"
        "M",
        "AMSMSASMAAXXAAAMAMMAMXMAAMMMMSMMSSSMMSMMSMSAXSAAMSSSMSAMASMMMMMMMSAMSM"
        "MMMMMMMMMSSMMXMAMMAMMAMMMXMAMAAMASAMXXMASXAAXMSSMSSXXMSMSAMASAMMMAAMA"
        "S",
        "SMXASASMMMSSSSMSMSAXAAMMSAMXXMAMAAXAXAAXAMMAMMMMMAMXASXMXXAXSXMAMMXMAA"
        "XAMXAAASMAAAMXMAMSSMMAMASMMSMAMSASMSXMSASMSMXXAAAAMXSMMAAXXXMASXSMXSA"
        "S",
        "MXMMMAMMMMAAXXAXAXMMMSSMAXMAMXAMMMMSMXMMASXMMMSMMMSMXSXMXASXMASMSSMMXS"
        "XSMSMSSSMSSXMAMMXAMXSASMSAAXXSMSASXMMAMXSAMSMMSMMMMXSAMMMMMASAMAMSAMX"
        "X",
        "SMSMMMMMAAMXMSXMAAMAXXAXMSXMSSSXSAAXMMSSMMMXSAMMAAAAMMAMSAXAMASAXXAMSA"
        "MXMAAMXXXAXXMSSSMASXSASASMMMMAAXASAMXSMMMMMAXAAMAXMAMXMSAXSAMXSAMMMMS"
        "X",
        "SAMXAASXSSXMAMAAXXSASXMMXMASMAAASMSMSAAAAAAXMAMSMSSSMSAMXASXMASMSMSMSA"
        "ASMXMMMSSMMSAMXASAMAMAMMXXMAMMMMSMMMAMAAAASMMSSXSAMXXAXMXMAASAMXSXXAA"
        "X",
        "MMMXMSAAAXXAXSMMMXAXSAXMXSSMMMMMMAAAMMSMMMSXMAMXXAAAAXXXMMMMMXSXXAAASM"
        "MMXSAAXMAAAAAASMASMMAASXSMSASAXMXAAMAXMMSXSAAAXXXAAAMSXMXMAXMASXSMMMS"
        "X",
        "MSSSMXMMMMMSXMAAMMSASMMMAMAAXXXSMSMSMAXXXSAMSASMMSSMSMSXAAAXSXMMMSMXXA"
        "XAAXXMSSMMMSMMMXMXSXSASASXSMSAMXMSMSSSMAXASMMSSMSAMSXMASMMMXSXMXMASAA"
        "M",
        "XAAAAXXMMXAAMMSMSAMMXAAMASMMXAMXAMXXMASMMSAMSAMMAXAAXAMXSSSSMAXSAXSSSS"
        "MMMXAXMASXMAMXXSXMMMMMMMMAMMMMXMMMXAAAAXMAMAAXAAXXMXASXMAAXAMAMMSAMMM"
        "A",
        "MMSMMMSMAMSMSAXAMXSSSSMSMSAMSSMMAMXSMXSAAMAMMSMMXSMMMSAXXXMAMAMMMSXMAM"
        "XAAXSMMASMSSSMXMAMMXAAXAMXMAAXAMASMMSXMAMSAXXMAMMASMMMSSSMMXXAMAMMSXX"
        "S",
        "AAAAMAAMSXMAMAMXAMAMAXAAASAMAXAMASAXAASMMSSMXMXXMXXMSXXXMMSSMXSAMXMMAM"
        "MXSMMAMASAAXXMASAMAMMXXXSASMSSXSASAAXAXMMAMSAAAMSMMAAAXMAMSMXMSXSMMAM"
        "X",
        "SSSSMXXMMAMSMXMASXMMAMSMXSXMASXMAMXXXMXAAAASAMAAAMMMMXMAAAAAXMSASXAMAS"
        "MAXASXMASMXSMSMSASXSSSMASASAMMAMXSMMSMMMXAMXXMXXXASXMXSXMMAAAXMASXMAS"
        "M",
        "AXAXASXXMXMAMAMAXAXMMMXMASXMAMXMASMSMSASMXSMMSMSXXAAXMSASMSSMMSSMMMSAA"
        "MASAMMSXXMAMASASAMAAAAMAMMMMMMAMXMAMMMASMSSXMMMASXMASXSXSSMSMSAXMASAS"
        "A",
        "XMAXSAMXMASMSAMXSSMMXMAMAMXMASASMMAAAXAMMXMXMAAMAMSMSAMAXMAXAXMASAXMMM"
        "MAMAMAAAMMSXSMMMAMMMMMMXXAMXAMAMAXAMASMSAAXAXMAXMASXMAMAAXXAXAAMSXMAM"
        "X",
        "SXAXMMXMXASXSXXMMMMSASXMASMSASMSXSMMSMMSXAXASMSMMMAASMXAMMSSSMASMSMXAX"
        "XMMSMMSXSAMMXXXMAMXSSMXXMAMXSSSSXSASXMMMMMXMMMSMXMMXMAMXMASMSMXAXMMSM"
        "M",
        "SAMXSMMSXASAMXMAAAASMSXSXMAMASXMAMXAXAASMASXMMXMXSMMMMMMXXXAXXXMMXXMAS"
        "MSAMAMAMMASASMSMMXAAASAMSSMAXAMXAMXSAMSAMMASAMASMASXSASXXAMAAAXSXSAMA"
        "S",
        "MAMAXAAXMMMXMAAXMMMSXXAMAMSMMMAMAMMMXMMSSMXMAXAXMXMMAXXAMSMMMXSASXMASM"
        "AMXSSMAAMXMASAAXSMMSXMXXAXMXMAMMSMAMAMXAMSASASASMXMAMASMMMMMMMMMAMASA"
        "M",
        "SAMXSMXXAXAASASAMXXMMMAMAMAASXMSXSASASMMXXMASMSSMMASMMMMSMAAAXSAMSASAM"
        "SMXMXSMSXSMMMMMSMAAMAMMMMSMMSAMAAMASAMXXMMXSAMASASMSMXMAXAASMMSMAMMMM"
        "M",
        "XXMMMASXSMSMSAXMMXSXAMSXMXSSMAXAXMASAMAMXMSMXAXSAAAXXAMXAMSMSMMAMASAXS"
        "XSXSASMMAAASAMMXXMMSASAAXAAASAMSMSASMXAMXSAMXMSMXMAMXAXASXMSAAXXSMXMA"
        "S",
        "SXSASAMXAAMAMXMXXAXMSSMAXAMAMSMMSMMMXSXMAXMAMSMSSMSSSMSXMMXXMASXSXAMXS"
        "AMXMASAMSMMMAMSAMXASAMMSSSSMSSMAXMASASMMMXAXMMMMMMAMMSMASMASMMXAMXMSM"
        "A",
        "AASMMASXMXMAMMMMMSSMMAMMMXSAMXXXAAAAXMASAXMAMAMXXXAAAAMMSXMASXMASAMXMM"
        "AMAMAMAXAXAXXMMMSMMSMMXXXAXASMMSSMXMAMAAXXXMMMSAAMASAXMAMMAMAAXSMSAAX"
        "M",
        "MXMXSAMMXMSAMMAXMASASAMMAMMXMXMSSSMMXXAMXASASMSASXMSMMMAXASAMAMXMXXMXS"
        "AMXMXSMXSXMXXSAXMXAXXXXXMMMMMMAMMMMMAMSMMASAMASXSXXMAXMAXMXMAMXMAMSAM"
        "X",
        "MXMASAXXMAXAMXMMSASMMASMAAASMMAAAXASMMAMMXXASXMASAAMAMMMSMMMSMSMMXXXAM"
        "ASMMMXMAMASAMSMSMMMXXXMXMXAAAMASAAAMXXAASMSAMXSAMXSXMXSSSSSMMMAMXMASA"
        "X",
        "XXMASXMMXSSSMXMMMAXAMAXXXMXMASMMMSAAMXMASMSMMASAMMMMAXAMXMMAAAAASASMSS"
        "SMAMAXMASAMAMMAAXAXMSMSASXSXSXMSMSXSMSSMMXSXMMMXMAMSXXXAAAXMASAMXAAMS"
        "S",
        "MXMAMAMXAAAMAASMMSMAMMSAMXMSMMAXXMMXAAMXAAAMXXMASXSSSSMXAMXXMSMSMASAAM"
        "ASMMSXSAMXMXMXXSXMSXAASASAMXMMMMAXAAMAMAXAXAAMAAMAMMXMMMMMSSMSSMSMMSA"
        "X",
        "MXMSSSSMMSSMSMSAAASAMMAMXAAAXMMMXXSXMXSSMSMMMXMAMAAAAXMMSMMAMMMAMXMMMS"
        "AMXAAAMMXMXSMSAMAAAMMMMMMAMMMAMMAMXMMSSMMSSSMMXSSMSMAAMXMAXMAXAXSAMMM"
        "S",
        "AMXMAAXAAAAXXAXMSMSXXXSXSMSMSASMSMMAXSAXXAAASMSSMMMMMMSAMAXXMAXXMAXAXM"
        "AXMXMMMSSSXAASASXMXMMMSAMAMASMSMXMXXAXXXAXAMAXSAXMAMSXSAMMSMMMMMSAMAA"
        "X",
        "AAMMMMMMMSSMMAMXAAMMMMMASXMASAMXAAMMMSAMXMMMSAMXXAMSMAMASXMASAMMSMSMSM"
        "MMSMXSAAAXSMAMAMMSAXSASXSASXSXSXAXMMXMMMXSXSAMMMXSXXXASXXMAAAAXASXMMS"
        "S",
        "MSAXXMXAAAMXMAXMMMMAMAMAMMMMMAMSSSMAAMXMMMSXMXMMMSMMMAXMMAAMMASXAAXXAA"
        "AAAAXAMMXMXMAMAMASAXMAXMAMXAMAMMXAXSASAAASMMXSMXXMMMMMMAMSSSMSMXMASXA"
        "X",
        "SAMAAMSSMSSMMSSMSASASAMASAXAMXMXXAAMASMSXAAXMMMSAMASXMASAMSXSAMMMMMXSS"
        "MSSSMMXAXSXMASAXXMSMMAMMXMMMMSMAMMASASASXSAMASAMXAAMAMMSMAAAAXMASAMMS"
        "M",
        "XAMMXMAAMXAXAXAASMXMSASAMASXXMSXSXMXXXAXMMMSXAAMMSAMAXXAAXXXMAMMSASAXM"
        "AMAMAXMMSAAMAXXMAAAXMMSAAXAXMAMXMMAMXMAMMSAMASASMSXXAMMMMMXMMMSXMASXM"
        "A",
        "MMMXXMSSMSAMMSMXMASAMAMAMMMXAASAMXMXMMXSASMMXMSSXMASMMSMMSSMSSXASASMMM"
        "AMAXAMAXSMSMSMSAMXMXAXMMSXMMXMXASMSMSXAMXSXMMSAMAAASXMSAAMMSAMXSMMMAM"
        "S",
        "XASAMMMXMMAMMXXSXMASXXMMMMASMMMMMAAAXAASXMAAMSMMXXMAAXSAMMAMAMMMMMMXAS"
        "XSMSMXMXMAXAXASAXMMXMXSAXAXSSXMMSAMASMSMXMAMMMAMMMMMAASXXSMMASASXAMAM"
        "A",
        "MMMMMAXAMXXMXSXSAXAMMXMSMMAMAMAMSMSAMMMSXSMMMAAMMSSSXMSAMSAMASAXSSSSMM"
        "XSAAAASAMXMASMSAMXMASMMASMMMAAAMMAMAMAAMMSAMAXAMAASMMMMASAXMXMASMXSSS"
        "S",
        "XAAAXMSMSAMAXMASMMSMSAMAAMAMASAMAAMXMMXMAMMXSMSAAAMAMXSXMSMXMSMSXAAMMM"
        "AMXMMMSASXSAMXSAMXSAMAMAMMXSAMSSMSMAMXMXASMMMSSSXXXAXMASAASXMMXMAXXMA"
        "M",
        "MSXSXXAXMAMMMMAMAAAAMASMMMMSASMSMSMASXMXAMMMMXXMMXMAXAMXXMSAMXMXMMMMAM"
        "XSXSXASAMXMASAMAMAMMXSAMXSAXASXAAASXSMSMMSAXMAMMMSSMMMSMMMMAASXMSMSMS"
        "M",
        "MMAXXSASMSMSAMXSMMXMMAMAMAMMAMASAAMMSAMXMSXAMAMXXMSMSMSXMASXSAXMAAXXAS"
        "AMAXMMMAMXSAMXMSMSMSAMAMAMXXMMMMSMSMSAXMMMXXMASAAXASXSXXMXSXMMAMAXSAM"
        "X",
        "AMXMAXASAAXXXXXSASAMSASAMSMMXMAMXMMMSMMASAMMSSXMXMAAAMAAMAMXSAMSSMSSXS"
        "AMXMXSASMXMASXMXAAAMXSAMSMSASASXMASAXMASAMMMMXSMMXAMXAMSMXAMAMAMAXMAM"
        "X",
        "MMMSSMMMXMMSSXMSAMAMSAMMMMAMXMXSMMAAXAXXMASXAXAMASMSMSXXMASXMXMAAAXXMX"
        "AMAMASAMAXSAMXAMSMSMAMASAAXAMMXAMAMXSXASXSAASMMMXMXMMSMAMXMASMMSSMMAM"
        "X",
        "XXAAAAXXXMAAXMAMAMMMSXMXAMXMMMAMASMSSMMSMMMMMSSSXSXMXMXMMMSAMXMSMSMASX"
        "SMXSAMAMSXMASMXMAAAMASXMMSMMMSMSMAMMSMMMAMXXXAAASXSMXXSMSXXAMAAAMASAS"
        "X",
        "SMMSSMMXXMMXSAXSAMXAXASXSSMMAMAXMMAMAXAMASXAXAAMMXAMMSASAAXXMAXMAMMAMX"
        "MAXMXSXMXASAMXXAMMMMXSAMXAAAAXAXSASXXAASAMXSSMMMSAAMAMAXAXMMSMMMSAASA"
        "X",
        "AAMAMASXMMSASMMSXXMXMSMAXMAXMMXSMSSMAMMSAMMMMMSMAXAMXSXSMXSASMSMAMMXXA"
        "MXMAAXMASAMASAMXMASMMMMMSXSMSMMMXXMASXMSASAASXAXMXMMASAMSSMAMAMXMASMS"
        "S",
        "SXMAMAMAMAMMSAMSXMASXAXXMSSMXSXAAAXMXSXMASAAXXMMXSAMXMAMAXSXMAAMSMAMXM"
        "SMSMSSMAMASXMXMASASAAXSAXXXXXAMSAMXAXMASAMAAMSMMMASXXMAMAAMAMSAMXMMMA"
        "M",
        "XXMSMMXSMXMAMAMXAMAMSMMXAAAAAXSMMMSAMMXXAXXXMMXAAMAMAMXMSMSAMSMXAMXSAA"
        "AASAAXMXSAMXAMXXMASMMSMASAMASMXMAMMMSMXMXMMMAXMASMSMMSMMSSMAMMAMMSAMA"
        "M",
        "SAAAASXXMMMSXMMSXMAMAXXXSSMMMMAMXSXAAAAMSSSSSXMMMMAXASXMAASAMMSXXSAMMS"
        "MSMMMMXMAXMXSXSXAXMXMAMXMMMXMAXSAMASAMXAAXXXXXMMSAMXMAAXMAXMSMAMASMSA"
        "S",
        "SMMSXMAXAAAMASMMSSMSSSMMMAXXMASMXASXMSXMAAAAMSMAASXSMSASMXMAXAAMSMMXMM"
        "XMMAAXSSMSSMMAMXMSMASASAMXXSXMASASMSMSMXASXSXXMSMXMASXSMSAMXAMAMXSASA"
        "X",
        "XAAAAXASMMMSAMAAXXAAAAAASMMSAAAMAMXXMAMMMMMMMASMMMAAASXMXMSMMMXMAAMXSA"
        "MXSMMXMAAMMAMXMAMAMMSXSASXMSAAXSMMMMMAAAMXMXMASXAXSASAMXMXXSMSXSAMMMS"
        "M",
        "SMMMMMXSXAAMMXMMMMMMSMXMMAXXMMSAMXMXSAMMAMMXSMSXSMSMMMMMMXAAAAMSMSMAMA"
        "MASAMXSMMMMXMMXMSMSXSMSMSAASAMXXMASASXSXXAMXAMAMXMMMMXXMSMMXAXMMASAAM"
        "X",
        "MXSAAMASMMMSSXXMASAAAMMSMMSXSAXMXAAAMAMSAXMAMXMASAXASAAAMSSSMSAAAAMASA"
        "MXSAMXXASASMMSAAAAAAXAXAXMMMMXMASMSASAAAMSMAMAXXAMASXMMXAASMMMMSAMMSS"
        "M",
        "XAMMSMASASXAXMAXASMSXMAAAXAAMASXXMMMSAMXMSMMXXXXMXMAXMMSXMAXAMMMXXMAMA"
        "XASAMMSMMXXAASMSMSMMMMMMMXSASAMMMMMMMMMMMXASXMMSXSASAAXSMSXAXAMASMMAX"
        "A",
        "MXXSAMXMXMMSSMSMAXMXAMSXSMMXMSMMXSMXSASXAMMAMSMSMSMSMSXXASMSSXSXMSXSSS"
        "MAMAMASXMXSMMMXAMXAAAXAXSXSASXSAXXXSSXSMXMAXXAASAMASMSMMXAXSMXSAXXMAM"
        "M",
        "MAXSASMSMXAXAAAMSMSMMXMAAXXXMXAMASAXMAXMSMMAAAAAAAAAAAASAMXAAXXAXAAMAM"
        "XXMAMMMASAMXAXXXXSMSSSSSMAMXMAMMMMAMMAMMSMSMSXSMAMAMMAAXSSSMAXMASXMXS"
        "X",
        "ASXSXMXAMXSXMMMSMAMASAMMMMXMAAMMASMSMSMAAXSMXMSMMMSMSMXMMMMMSMSXMMXMAM"
        "AMMSMSSXMXMMMSMSMAAAMXMAMXMMMMXSAAASMAMXSAMXXMXMSMXSSSSMAXAASXMXMMMMA"
        "M",
        "MXAMXSSMSMXMXAXAMAMMMAXSAMMAMMSMXSXAAXMSMXXAAXMXMMMXMMXMSAMSAAXMXSASAM"
        "ASXXAXXMSASXMAMAAMMMXXXXMASXMXAMXXAXMASXMMMXXASAMXXMAXAMMSMMMMMMSXSAS"
        "X",
        "XMAMAMAXXXAXMASMSMSXSAMMAMSASASXSMXMSMMAMSMSMSAASAMAXMAMMAXSMMMMAAXMXS"
        "ASAMSMSASASMSMSMXXMMMSMMSAMAXMMMSMASMXSAMSMMASAMSMSMAMXAXSAMXAAAXMAMX"
        "M",
        "MSAMXSMMSSMSMXMAAMMXMAMSAMXAMAXSXMAMXASMSSXAXMMMXAXAMSASXSMXASMMSSMMXS"
        "AMXMMAAAMAMAAAAMSXSAAAAAMASXMMSAXAAXMASXMAAXSMMXAAAXSSSXXMMMMMSSMXSAM"
        "X",
        "MSMSAMXAAAXAMAMSMSSMSAMMASMAMMMSXSMSXMMXAXMXXSASXSMSXSAXAAXMXMAAAMXXAM"
        "MMMMMSMXMAMSMSXSAASMSSMMSXMASAAAXMXSMMMMSMSMXAXSMSMMMAMSSMSSMMXAMAMMM"
        "M",
        "ASMMXXMMMSMXMMMXAAXASAMSAMXAXAMXAXAAMMSMSSSMASXSAMAMMMXMSMMMXSMMMSXMAM"
        "SAXMAMMMSAMXAMXMMMMMMAXAXXMAMXSSSMMAMMAMAAXMXSMMAXXMSAMXSAAAASXXMASAM"
        "A",
        "XSMSMASMMXMSAMAMMMSXSAMMMSMSXSMSSMMMSAAXAAAMXMAMAMXMXXSAXASAMAXSXXXAMX"
        "MMSMASXAXXXMAMAXXSMSSSMMSMSMSAMAAXXMASASMMMSAXAMAMXXMAMXMMMSMMAXSASAS"
        "X",
        "MXASXMSASMASAMASAXMXMMMAAAAMAMAXMAXAMXSMMSMMAMXMMMXSAXMASAMSAMSAAMSSXX"
        "AAMMMMMSSSSMSSXMAAXAAAMXAAAAXAMSMMXSASASAMAMASMMMSSMSMMASAMAMMSMMASAM"
        "M",
        "AMMMAXSAMMAMAXASMMXAMXXMSMMMAMAMXXMXXAMXMAAMASXSAAXMAXMAMAMXSXAMXMAMMS"
        "MSSMMMXMAMXAAMAMXMAMSMMMMSMSMMXMXMAMMSXSAMMXAXXAXMAAAMXASAXXMAXAMAMAM"
        "A",
        "SAASMMMAMMSSSMMSASMMMAXXMXAMAMAAAXSSSMSXSSSMMSAAMAMMAMMASMMXXSMXAMSXMA"
        "AXXAASMMAMMMMSXMASMXAMAXMAAXMSASAMAMAMXMMSSMMSSSMXMMMSMAMAMSMXSAMSSMM"
        "S",
        "MSMAAXSMSAAAXXMMMMAAAXMXASXXAXMMSXAAXAXXMMXAXMMAMXAXASXAMAMXXXXSAMXASM"
        "SMSSMMASXMXMXMASXSMXMSMSMMSMAMASASASMSASMAAAAAMASXAAAAMSMSMMAAMAMMAMA"
        "X",
        "XAMSMMMASMMSMMMASMSMSSMMXMASXSXAXMMMMMMXSAMMXMMXMAMXAMMMSAMXAXMAMXSAMA"
        "AXMASXXMXMASASAMXMXMXAAXXSMMXMAMAXAAMSAMMMSMMMMAASXMMXXXAMAMMMMSMSAMX"
        "S",
        "AXAAMAMAMSAMXASXSAAAAAASAMXMMAMXSAASMMAAMASXMMAASXSSMMSAMASAXSSMSXMAMS"
        "MMMXMXAAAMXSXSAMXMAAXMMMXMAMSMAMXMASMMXMAMMAXXMSASXSXSAMAXXMAAAXASXSX"
        "S",
        "MMSMSAMXSMMMSXSMMMMMXSMMAXMAMMSMSXMAAMMSSMMMAMSMSAMAAAMMSMMMMAAAAXSAMM"
        "XXSASMMSXSXMASASASXSXSAAAMAMXSASXAAXXAASASXMMXMXAMAMMMXSMMSSMSSMAMXMA"
        "S",
        "XAAXXMSXMASAMXMAXMXSAMASAMXAMXMAMAMXMMXAMAAAMAMAMAMMMMSXAAAAMSMMMXMXSM"
        "AMSASXMXMAMXAXASASAMASMSSSXSAMXMMMMXMXMSASAAXSAMMMAMXXMAMAAAXMXMXMXMS"
        "M",
        "MSSMSASXSAMXSASMMXAMAXAMXMSASMSSSXMAXSMSMSASMSSMXAXXAAXXSSSMXMAMXSXAAM"
        "AXMMMAXMXAXMXMAMAMAMAMXAAAAMASXMSMSASMXMASMMAAASASASXSMSMMSSMMAMAMXMA"
        "M",
        "AXAAMSMMMXSSMAAMMMMSSMMSXXAASAAXMASXMAAMAXAXXAAXMMXSMXSAXAAXASXMAMMSMS"
        "MXAAMXMSMSXSAAAXXXAMXSMMSMMSAMXAAASAMXAMXMMMMXXXAXXAAAAAAXXMAMAMAMMXM"
        "S",
        "SMMMMXMASAMXMAMAAAMAXAXMMMMXMMMMSAMSAMXMMMSMMSMMXSAXMAXXMXMSMMXMAMAAXA"
        "MSMMMSXSAAASXMXSMSXSAXMXXMASASXSMMMAMSMSMMXAMSSMSMSMMMXMSAXMSMSSMXSAX"
        "A",
        "MMSXXXSXSMSMSASMMSMMSMMXASAXMAMMMAXXSXXXXSAMAAXMAMMSMMXSASXMXXXMXSXXSX"
        "MAAAXMAMXMMMMSMAAAXMASXMAMMSXMAXXXXXASAMXMMXMXAAXAMXAXSAMMSXXAMAAAMAM"
        "M",
        "AAAXMASASAAAAAMAMMXAAXXMMMMXMASXSSMAXXSMMSXXSASMXSASAAAAXMAASMXSASXASM"
        "SMMMAMXMMXXAAASMMMSMMSMSMMAMAMAMAMSAAMMMAXMMMSXMMAMSXXAAAAXMXMSMMMXSA"
        "X",
        "MMSMSAMAMMMSMSSMMMMSMSMAAAXMAXSXAAMMMASAAMMXXAMXAAXXMMSSMSMMAAAXAXMXMA"
        "SASMSAMXMMSMSXSXAMAAAXMAXMASAMXSAAAMAMXSMMMAXAAXXXXMXXSSMXMMAMAXAAAAS"
        "X",
        "XMAMXSMAMSMXXAAASMMAAAASXSSXSASMSMMMSASMMXAXMSSMMSSXSMMAAXAXMMMMMMMMMX"
        "MMMAAMASXAAXXXMXSSSMMSSMXSAMASXMXSXXXMAMXAXXSMSMXSAMMMMAMSMSASXSXMASX"
        "M",
        "MSMMMMSXMAAXMMMMMASMSMXMXAXAXMSAAAAAMASXMASXMASAMXAXSASMMMSXXAXAAAAMMM"
        "SAMXMXSAMSMSXMSAMXMMAMXAAMASMMXXXMASMMSSSMSAMAXAMMAXAAMAMAAMAXXMMXMAX"
        "A",
        "XAAAAMAMSMMMSMASXMMAXMXSXMMSMASMSSMSMAMXMAXAMMSXMMXASAMAAMMSSMSSSSXSAA"
        "MASMXXXMAXAMAMMXSAMXAXMMMMAMAAAXMXMMMAMAMAAXMAMAMSMMSMSMSXMSXSASMMMAS"
        "X",
        "SSSMSSXMASAAXXAMAAMAMXAAAXAMMMMAXXXXMXXXMXSAMXSMMASASMMXMMMXMXAMAAXSMS"
        "SMMMMMMXAMAMXMAAXASMSMSMAMASMMMMMAAAMXMAMXMXMMMAMAAMAASASMAAASXMASAMA"
        "A",
        "XAAAXAAMAMMMMMSMSMMSSMMSSMSXMXMMMSSXAASMMASXMAMAXXAAMXXXSASASMMSAMXMXA"
        "AASXAAXMASXMMMMMXAMAXAMXAXAMXMXAXSSMSXSXMMXMMMXXXMMMMMMAMXMMMMASAMAMM"
        "X",
        "MSMMMSMMSSSMSXMAAXAAXAMAMAAAMMMSAAMMMMXAAASAMXMMMMMMMXMMSASASAXAAXAMSS"
        "SMMSSSSSXAAXXSASMSMAMAMSMSMASAMXMXAMXAXAXSASXMASMSXXAAMAMAXXXXXMASXMX"
        "S",
        "AXASAAAXAAAAXAMSMMMSSMMASMSMMAAMMXMAMSSSMMSXMASASAXAMMMAMXMASXMMXMXXAA"
        "AMXAMMMMMSMMMSASMAMXSAMAMAMMSMMXSMSMSXSMMSASXMASAAMSSMSXSMSMMSSSXMXSA"
        "M",
        "MSAMSSMMMSMMMXMAXASAMMSXMXAASMMXSASMSMAAMAXAMAXMXXMSXMMSSSMXMASASMSMMS"
        "MMMXSXXXAMASXMMMMSSMSXSXSASXMASAXXAAAMAAAMXMXSAMMMMAAMMAXAAAXAAXXSXMA"
        "S",
        "AAXAXXAAXMAAAXSXSXSASMMAMMMMXAAAMXMMAMXMMSSSMSSSSMXMAMAXAXMASXMAAAAMXM"
        "AXMMMAXSMMAMXAAAXMAMXXMXMMMAMAMXSMMSMAXMASXSAMMSAAMXSAMMMMMMMMSMMMXSA"
        "M",
        "AMMSAMSSMSSMSXMASMSAMXXMMSXASMMMSAMSSMMSMMAXAAAAAXAXAMMMAMSXSXMXMSMSAS"
        "MSSMMAMMAMSMSSMSSSMMSASAMSSMMMSMAXXAXXXXASAMXSASMSAXMAAXMASAMXMMAAASA"
        "S",
        "XXAXAMXAMXXAMXMASASAMXXSAMMMSMAXSAMAAAAAXMAMMMXMMSMSSMXMAMSSSXXXMAMSAS"
        "AAAXSMSMAMXAMXMMXAXAMAMXSAAAMSAXAAMSSSSMAMAMAMASAXMSMXMASASASASMXXASA"
        "M",
        "XMAXMMMMXMMXMAMXSXMMMAAMAMAXMMSXMAMSMMMSAMXMAXMXXXAAXMAMAXXASAXSSMMMMM"
        "MMMMXAAXAMMXMSXMAMXAMAMMMMSMMAAMXSAXAXXAXSXMASXMMMXAAASXMASMMASASXAMM"
        "M",
        "XSSMSAAXSASASASAMMSMMXSSSSXSAAMASAMASMXMASASXSASASMMMSSSSSMMMSMAASMAMA"
        "XXSMMSMSMSSMAXMAXSAXSAXMXAXAMMMMXAMMAMMSAMXSMMMAXMSMMMMAMAMAMMMAMMSMA"
        "M",
        "AAAASXMSAAMASAMXMSASAMXAAXXAMASMMSMAXXAXXSAXAXXMAAXXXAAAMXASAXMSMMSASM"
        "XMAMXAAAMAAMMMMMAAMMSMSSMMSSMSSXMMXSAMAAAXMXAMSSMXMASMSMMXSMSXMSMAAMA"
        "S",
        "SMMMMMXMMMMXMAMAXSASMSMMMMAXMASXMAMMSXSMMMMMSMXMMMMMSMMMSSMMMSMAAMMMSX"
        "ASXMSMXMMSXMMAMXMMXAXAAMAAAAAAMMAXAMAMXSXMSMMMAAMXAAAXAAXAAXMAMMMSMSA"
        "S",
        "XASXXXAMMSMXXAMXAMXMASXAMXAXSXMASMXMAMXAMAAAMASXSXAMAXXAMMAAAAXMSMAXXM"
        "XMAMMSMXAMAMSMSAXXSMMMMSSMSMMMSSSMMSXMXXAAXASMSSMSXSMSXSMAMMSXMAAXXMA"
        "S",
        "SXMAXSAXAAAMASXMMMXMAMSMSAMXAXMXMSXMAXSAMXMMSMXAXSMSMSMMSMXMSSSXMMMMMM"
        "XSMMAAMMASMMAASXSASAAXMXMAXMMAMXMXMAMXASXMXSMAAXAMAMXMMXMAXXAAMMXSAMX"
        "M",
        "MMMXMMAMXSAMAAASXSAMXXMMAMMMMSXSASMXXXMMMAMXMAMSMXXAXXAMAMAAXAXAMMSMXA"
        "AMXMSSXSAMXSMMMASASAMXSMMSMXMSMSXMASXMASAMSMMMMMAMMSAMAMXAMASAMAASXMA"
        "S",
        "SASASXXMMAAMMSXMASXXSASXMSAAXMAMAMMMSSMSMMXAMSMMAXSMMSSMAXMSMMMMMAAAAM"
        "XMAMMAXMASASXAXXMAMMXAXAXXXXSAAASMMMASASXMAAAAXMAXXSAMSMMXSAMSSMMSASA"
        "S",
        "XMSAMMMSXSXMAMAMXMAXSAMXAXMMAMAMAMMAMAAAASXMMMAMSMAAAAMMMSMMAXAASXMXXX"
        "MXXSMSMSAMMXMMASMXMMMXXXXMAXXMSMXSASXMASXMSSMSSSXSAMXMAAXAMAMXMMXSXMM"
        "S",
        "XMMXMAXXAXXMXSAMXMXMMSMMSMMSMSAMXMMAMMMMXMAMASXMXSMMMMSAASASXMMXXAAXSM"
        "SMMMMMMMXXMAMXMAAAAXASXMSXSASXMMASXSMMAMAXAAXAAXMMAMXSXSMMSSMAMSAMSSM"
        "X",
        "XMASXSMMMMMMMSAMXMXSAMXAAAAAMAMMSMSMXMAXASAMASAMAMXSAMMMXSAMMAMSSSMMSA"
        "AAAAAAXSSSSMMAXSAMXMXSAAAAMSAAXMAMXXXMASXMASMMSMXSAMAMMMAXAAMAMMASAMX"
        "A",
        "XMXMAMXXAAAAASAMSAXMASMSXXMXMAMXAAAAASMSMSAMXSAMXSASASXSXMASXSMMAMXAXS"
        "MSSSMMSAAMASXXXAXSXMASMMMXSMMMMMSSMMASMMXSXMASAAASMSMSASXMSSMAMSXMMMM"
        "X",
        "SSSMSMAMXSSMMSMMSAMSMMMMASMSSSSSMSMSMAAAAMMMASXMXMXSAMXAMXSAAAXMAMMMXA"
        "MXAAASAMXMAMXXSSMSAXAMAMMXMAASAXXAXXAMAAAXAAXSMSMMAAXMASAAAXXAXMAMASM"
        "M",
        "MXASAMXSAMAXMXXAXAMXSAMXAAAAAAAAAMAXASXSXSAMXSASMSAMXMSXASXMMXMXAMXXSS"
        "MSSMXMAMXMAMXMAXASXMASAMMASMMSMSSSMMMSMMSAMXMMMMXMMMXSAMMMMXMXXSMMASA"
        "A",
        "AMXMMXAMASAMXAMXSAMXSMSMSMMMSMSMMMASAMAXASMSASMSAMXMAAXAMAXXSSMSASMXSA"
        "MAXXAXXMAMASAMXMXMMMXMMXSASAMXAMMMAAAAXSAMSMMAASASASAMXSXMXSSSMAXMXSM"
        "M",
        "MAAMXMXMAMXMMSSMAXXMMXXAXXXXMAXAXXMMAMXMMMAMXXXMXMASXSSSSSSMAAAASAMXXA"
        "MXSSMMSXMSAAAMSMSAMXASXMMASXMMMMASXMMMSAAXMASMMMASAMXXMXMMXXAAAMSXMMX"
        "S",
        "MSSSMMSMMSXSAAAAMMMMMAMXMASXSAMMMXXSXMXMSMMSMSMMMSXMMXMAAAMMMMMMMMXSSX"
        "MMMMMXMAMMMXMMSAXASMMSAAMAMMMSMSMSSSXXMMMMSAMXSMXMXMXSAAMSMMSMMXSASMA"
        "A",
        "MAMAMAMAMAASMMMSAAMASAXASXMMXAMXAXMASMXAAAXAAASXMMMSMSMMMMMASAMXXXMMAM"
        "XXAAMMMMMAMXSAMAMXXAXSXMMMAAXAAAAMAMMMXAAXMASAMXMASMMSSMSAAMAXAXSAMMS"
        "S",
        "MASMMMSAMXMMAXAMMMMAMMMMSAXAMSMMMSAAASMSMSSMXMMXAAAASAAXMMSASASMMMXMAX"
        "SXMMSAAASXMAMASAMXSAMXAXAXSXSMSMMMAMAAXMSMMAXASAMAXXAMAMXMSMXSMMMAMAM"
        "M",
        "XMMXAASAMXMSXMXMASMSXSAMXAMSSMAAXMMMMXMAXAXXSXMSSMSSSSSMSAMASXMASASMSM"
        "SASASMSMSAMXMAXMAMXSAMMXXXAAMAMAASMSMXSAAMMSXMXAMXMAMSAMSXXAAAAASAMAS"
        "X",
        "SXAMMMXAMAXMASXMMXAAAXAXMAMXAXMMMMSMSAAMXMAXSAMAAAXAMAXAMMSAMAXSAMXAAA"
        "SXMAMXXXSASAMSSMSXAMMXXMMAMXMAMSMXAAAXMXMSAAASMSMSMAMMAMAMMMXSMMSXXXS"
        "A",
        "AMAMXSSMSXXMAMXXXMMMSSMMMXXSAMXAAXAASASXAXMASAMSMMMSMMMSMMMMSXMXAMASMM"
        "MMMSMAMAMXMAXMAAMMMMASXSMAMSMXXXAMSMMMXAXMMMMMAMAAMSXSAMMAAAAXAMXXSAS"
        "M",
        "MMXMAMAAAASXMXXMXAXAXAXAXAXMAASXSXMXMAMXXSMMSXMAAXAMASXAXMAASASXAMXMMX"
        "AAAAMAMAMXXSMSMMMXMAMSAASXMAAXMMSMMAASMMSMSMXMAMSMSAASMMMMSMMSSMAAMMM"
        "X",
        "XAAMSSMMMAMAMASXMMMXSMMMMMSSSMSAXAMAMAMXXMAAMASMSMASXMSMMMMMXMASXXXSXS"
        "MMMSXXMAXXAXAMXAAXXMSMMMMXSMSSXAAASMMSXAAAAXXSAXMXSMMMMAMXXAAAAMXMXXA"
        "X",
        "XSXXMAMXXMSXMASXAXMMMXASAXAXMAMAMXSASXMMXSMMSAMAMXMMAXXXASMMSAMAMXAXXM"
        "MSXMASXMSMAMAMMXAXMMAAMMMXSXAMMSSMMMAMMMMSMSAMXXAAXAMXSAMMSMMSSMAMAMA"
        "M",
        "MAMXXXMAXMXMAMMMSMMASXXSASMXMSMSMXMAMXMAXSMMMAMAMASXMMMXMAAAAXXAXMAXSX"
        "AMAMAMAAXXAXSMMMMAASMMMAMMMMMSAAXAMMSMAMAMXSXMXMMMSSMAMXXXAAAAAMAXASA"
        "S",
        "XSXSMSMSMASXSMSMMMMASMAMAXMAMAAASXMAMXMSXMAXSMMMSAMXXMAMMSMMSMSXXASMSM"
        "XSMMSSMMMXXXXAXAMXXMAXSAXAAAXMMMXXMAMMAMXSMMAMXAAAXAMXSAMSAMMSSSXMAMA"
        "S",
        "AMASXAAAAXXAMAAAMSMMXMAMXMSSSMMMMMSSMSAMASXMAASAMASXSMXSXAAMMAMMMXMAXA"
        "MAAAAAAXXASASMMXSXASXMSASXSSSSSSSXMASMMMXSASAMMSMMSMMAMAXSMMXXMAMMSMA"
        "M",
        "AMAMSMSMSMMMMSSSMAMAMMSXMXAMXAAAXMAAMMAMAMAASXMAMAMAAAMSMSSMSSSMSMMSMS"
        "ASMMSSSMSXMASASAMMAMAAMAMMAMXAAAAMMAMAASXSASXSAASAAXMXSSMMAXXAMAMAXAM"
        "X",
        "SMAMXXAXAAAAXMAXMMMASXMASMMSXSSMMAXMASXMXSMMXMSSMXXSMMMMAMXAAAXAAXXAAM"
        "MXAMAAAAAXSXMAMASXMAMXMMMASMMMMMMMMSMSMMAMAMAXMAMXSMSXMAMXAMSXMXMXSSX"
        "X",
        "ASXSXSMSMSMSSMAMXXMAXXMXMAMAAMAXAMMXMSXMAMXAMMAXXAMXMAMMXMMMMMMXMSMMSM"
        "ASXMMSMMMAMAMXMXMXXAMMSSMAMMAAXAAXMXMXAMXMSMMMSMSAXASXMAMMSMMAXSXAXAM"
        "M",
        "AAMMASAAXAAXMMSMSMSMSASXXXMXMMAMMXMAMXXMASAMAMASXXAAXSXMAXAXXXSAASMSMM"
        "XMAMXAXXMAXXMASMMMMXSAAAMSSSSSSMXSAAXXAXMAXAMXAAAAMMMAMXSXMASMMMMMSMA"
        "A",
        "XXAMAMMSSMSMXAMSMAAAXAXAASMSAMSMXXXMSMMSASASMSASMSSMSMAMMMMSMAXMXMMAAA"
        "XSAMMSMXSSMMMXXAAAAAMMSMMAAMAAXMASMMMSSMSMSXMMMSMSMXSAMXMAMXMAMAAAAXX"
        "S",
        "MSSMMSXMMMMXMASAMMMSMMMMMAAXMAMMXSXXAAXMXSMMXMAXAMXMAMAMXXAAMXMSASMSXM"
        "MXASAAXXXXAXSSSSMSMMXMMAMMXMMMMMMXAXXAMAAXMMSMMAXMAAMMSSMAMSSSMSMSSSM"
        "X",
        "XAXAASAMXASAMXSXSAXAASAASMMMMAXSAMXXMSMSXSASAMXMSMSSMSMSAMSXMMAMASAMSX"
        "MMXMMSSMMMSMAAXAXAMMAXSXMAMXXMAAMXMSXMMSMSMAMASMSMMMSMAMXASAAAXMAMAAM"
        "X",
        "SSSMMSSMMMSMSMMASXSMMMXXXAMXSMMMMSSMAMAMASXMXXXAXAMXXAXMAXMASXSMAMAMAX"
        "MASAMXAAAAMMMMMXSXSXMXXAMMSMASXMSAAAMXXAAXMASXMAMAXMAMAMXMMMSMMMSMSMM"
        "S",
        "XXAMXMXSXAXXAXMMSASXSSMMSSMMMXAAAAAMXMAMAMAXMMSAMXMMMMXMMMSAMAXMMMMMMX"
        "AASAMSSMMXSAXXAMMASAMXXMMAAMXMAASMSMSXSMMMSASXMASAMSASXSXMAMAMXAAXXAX"
        "A",
        "MSMSAMXAMASASXMXMAMAAAAMAMAAAMSSMSSMASXMSSMMAASAMASXMSAAAXMAMXMASASAXX"
        "MASAMXMSMAXMAMSAMASMMSMAMSXMAMMMMAMASAMMSMMASXMXMMXSASAAMXSSMSMMSSSSM"
        "M",
        "ASASXSAMXAMAMASAMAMMMSMMASMMSMXAXMAMASAAAAASMXSAMAXAAASXMXSAMSAMSASASX"
        "MASAMXAAMMSXAXMSMXMXAASAMAASXSAAMXMAMAMAAAMAMXMAMSAMSMMAMAMAMXAAAMAAA"
        "X",
        "SMAMMMMXAMMAMXSXSSXMAXXSMMXAMXSMMSAMXSXMSSMMMXSAMXSMMMXXSASXSXSAMXMMX"
        "MMXSXMMSMSXSMXSXXMASMSXSSSXMASMXXSAMXSMMSSSMXSXSXSMMSXMASMXSAMSMMSMSM"
        "MM"};
    return data;
}
}  // namespace aoc2024::day4