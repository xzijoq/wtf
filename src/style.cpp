#include "style.h"

fmt::text_style eStyle =
    ( fg( fmt::color::navy  ) ) | ( fmt::emphasis::bold )
    |( bg( fmt::color::blanched_almond ) | ( fmt::emphasis::underline ) );

fmt::text_style wStyle =
    ( fg( fmt::color::yellow ) ) | ( fmt::emphasis::bold ) |
    ( bg( fmt::color::black ) | ( fmt::emphasis::underline ) );
fmt::text_style okStyle = fg( fmt::color::steel_blue ) | fmt::emphasis::bold;

fmt::text_style fwStyle = fg( fmt::color::floral_white ) | fmt::emphasis::bold;

fmt::text_style orStyle = fg( fmt::color::dark_orange ) | fmt::emphasis::bold;

fmt::text_style grStyle = fg( fmt::color::azure ) | fmt::emphasis::bold ;
fmt::text_style yeStyle = fg( fmt::color::yellow ) | fmt::emphasis::bold;
fmt::text_style liStyle = fg( fmt::color::lime ) | fmt::emphasis::bold;



void printallstyle()
{
    fmt::text_style omega = fg( fmt::color::alice_blue ) | fmt::emphasis::bold;
    omega                 = fg( fmt::color::antique_white ) | fmt::emphasis::bold;print(omega,")= 0xFAEBD7, style is imba\n"); // rgb(250,235,215)
        omega=fg(fmt::color::aqua                    )|fmt::emphasis::bold;print(omega,"aqua                    )= 0x00FFFF, style is imba\n"); // rgb(0,255,255)
        omega=fg(fmt::color::aquamarine              )|fmt::emphasis::bold;print(omega,"aquamarine              )= 0x7FFFD4, style is imba\n"); // rgb(127,255,212)
        omega=fg(fmt::color::azure                   )|fmt::emphasis::bold;print(omega,"azure                   )= 0xF0FFFF, style is imba\n"); // rgb(240,255,255)
        omega=fg(fmt::color::beige                   )|fmt::emphasis::bold;print(omega,"beige                   )= 0xF5F5DC, style is imba\n"); // rgb(245,245,220)
        omega=fg(fmt::color::bisque                  )|fmt::emphasis::bold;print(omega,"bisque                  )= 0xFFE4C4, style is imba\n"); // rgb(255,228,196)
        omega=fg(fmt::color::black                   )|fmt::emphasis::bold;print(omega,"black                   )= 0x000000, style is imba\n"); // rgb(0,0,0)
        omega=fg(fmt::color::blanched_almond         )|fmt::emphasis::bold;print(omega,"blanched_almond         )= 0xFFEBCD, style is imba\n"); // rgb(255,235,205)
        omega=fg(fmt::color::blue                    )|fmt::emphasis::bold;print(omega,"blue                    )= 0x0000FF, style is imba\n"); // rgb(0,0,255)
        omega=fg(fmt::color::blue_violet             )|fmt::emphasis::bold;print(omega,"blue_violet             )= 0x8A2BE2, style is imba\n"); // rgb(138,43,226)
        omega=fg(fmt::color::brown                   )|fmt::emphasis::bold;print(omega,"brown                   )= 0xA52A2A, style is imba\n"); // rgb(165,42,42)
        omega=fg(fmt::color::burly_wood              )|fmt::emphasis::bold;print(omega,"burly_wood              )= 0xDEB887, style is imba\n"); // rgb(222,184,135)
        omega=fg(fmt::color::cadet_blue              )|fmt::emphasis::bold;print(omega,"cadet_blue              )= 0x5F9EA0, style is imba\n"); // rgb(95,158,160)
        omega=fg(fmt::color::chartreuse              )|fmt::emphasis::bold;print(omega,"chartreuse              )= 0x7FFF00, style is imba\n"); // rgb(127,255,0)
        omega=fg(fmt::color::chocolate               )|fmt::emphasis::bold;print(omega,"chocolate               )= 0xD2691E, style is imba\n"); // rgb(210,105,30)
        omega=fg(fmt::color::coral                   )|fmt::emphasis::bold;print(omega,"coral                   )= 0xFF7F50, style is imba\n"); // rgb(255,127,80)
        omega=fg(fmt::color::cornflower_blue         )|fmt::emphasis::bold;print(omega,"cornflower_blue         )= 0x6495ED, style is imba\n"); // rgb(100,149,237)
        omega=fg(fmt::color::cornsilk                )|fmt::emphasis::bold;print(omega,"cornsilk                )= 0xFFF8DC, style is imba\n"); // rgb(255,248,220)
        omega=fg(fmt::color::crimson                 )|fmt::emphasis::bold;print(omega,"crimson                 )= 0xDC143C, style is imba\n"); // rgb(220,20,60)
        omega=fg(fmt::color::cyan                    )|fmt::emphasis::bold;print(omega,"cyan                    )= 0x00FFFF, style is imba\n"); // rgb(0,255,255)
        omega=fg(fmt::color::dark_blue               )|fmt::emphasis::bold;print(omega,"dark_blue               )= 0x00008B, style is imba\n"); // rgb(0,0,139)
        omega=fg(fmt::color::dark_cyan               )|fmt::emphasis::bold;print(omega,"dark_cyan               )= 0x008B8B, style is imba\n"); // rgb(0,139,139)
        omega=fg(fmt::color::dark_golden_rod         )|fmt::emphasis::bold;print(omega,"dark_golden_rod         )= 0xB8860B, style is imba\n"); // rgb(184,134,11)
        omega=fg(fmt::color::dark_gray               )|fmt::emphasis::bold;print(omega,"dark_gray               )= 0xA9A9A9, style is imba\n"); // rgb(169,169,169)
        omega=fg(fmt::color::dark_green              )|fmt::emphasis::bold;print(omega,"dark_green              )= 0x006400, style is imba\n"); // rgb(0,100,0)
        omega=fg(fmt::color::dark_khaki              )|fmt::emphasis::bold;print(omega,"dark_khaki              )= 0xBDB76B, style is imba\n"); // rgb(189,183,107)
        omega=fg(fmt::color::dark_magenta            )|fmt::emphasis::bold;print(omega,"dark_magenta            )= 0x8B008B, style is imba\n"); // rgb(139,0,139)
        omega=fg(fmt::color::dark_olive_green        )|fmt::emphasis::bold;print(omega,"dark_olive_green        )= 0x556B2F, style is imba\n"); // rgb(85,107,47)
        omega=fg(fmt::color::dark_orange             )|fmt::emphasis::bold;print(omega,"dark_orange             )= 0xFF8C00, style is imba\n"); // rgb(255,140,0)
        omega=fg(fmt::color::dark_orchid             )|fmt::emphasis::bold;print(omega,"dark_orchid             )= 0x9932CC, style is imba\n"); // rgb(153,50,204)
        omega=fg(fmt::color::dark_red                )|fmt::emphasis::bold;print(omega,"dark_red                )= 0x8B0000, style is imba\n"); // rgb(139,0,0)
        omega=fg(fmt::color::dark_salmon             )|fmt::emphasis::bold;print(omega,"dark_salmon             )= 0xE9967A, style is imba\n"); // rgb(233,150,122)
        omega=fg(fmt::color::dark_sea_green          )|fmt::emphasis::bold;print(omega,"dark_sea_green          )= 0x8FBC8F, style is imba\n"); // rgb(143,188,143)
        omega=fg(fmt::color::dark_slate_blue         )|fmt::emphasis::bold;print(omega,"dark_slate_blue         )= 0x483D8B, style is imba\n"); // rgb(72,61,139)
        omega=fg(fmt::color::dark_slate_gray         )|fmt::emphasis::bold;print(omega,"dark_slate_gray         )= 0x2F4F4F, style is imba\n"); // rgb(47,79,79)
        omega=fg(fmt::color::dark_turquoise          )|fmt::emphasis::bold;print(omega,"dark_turquoise          )= 0x00CED1, style is imba\n"); // rgb(0,206,209)
        omega=fg(fmt::color::dark_violet             )|fmt::emphasis::bold;print(omega,"dark_violet             )= 0x9400D3, style is imba\n"); // rgb(148,0,211)
        omega=fg(fmt::color::deep_pink               )|fmt::emphasis::bold;print(omega,"deep_pink               )= 0xFF1493, style is imba\n"); // rgb(255,20,147)
        omega=fg(fmt::color::deep_sky_blue           )|fmt::emphasis::bold;print(omega,"deep_sky_blue           )= 0x00BFFF, style is imba\n"); // rgb(0,191,255)
        omega=fg(fmt::color::dim_gray                )|fmt::emphasis::bold;print(omega,"dim_gray                )= 0x696969, style is imba\n"); // rgb(105,105,105)
        omega=fg(fmt::color::dodger_blue             )|fmt::emphasis::bold;print(omega,"dodger_blue             )= 0x1E90FF, style is imba\n"); // rgb(30,144,255)
        omega=fg(fmt::color::fire_brick              )|fmt::emphasis::bold;print(omega,"fire_brick              )= 0xB22222, style is imba\n"); // rgb(178,34,34)
        omega=fg(fmt::color::floral_white            )|fmt::emphasis::bold;print(omega,"floral_white            )= 0xFFFAF0, style is imba\n"); // rgb(255,250,240)
        omega=fg(fmt::color::forest_green            )|fmt::emphasis::bold;print(omega,"forest_green            )= 0x228B22, style is imba\n"); // rgb(34,139,34)
        omega=fg(fmt::color::fuchsia                 )|fmt::emphasis::bold;print(omega,"fuchsia                 )= 0xFF00FF, style is imba\n"); // rgb(255,0,255)
        omega=fg(fmt::color::gainsboro               )|fmt::emphasis::bold;print(omega,"gainsboro               )= 0xDCDCDC, style is imba\n"); // rgb(220,220,220)
        omega=fg(fmt::color::ghost_white             )|fmt::emphasis::bold;print(omega,"ghost_white             )= 0xF8F8FF, style is imba\n"); // rgb(248,248,255)
        omega=fg(fmt::color::gold                    )|fmt::emphasis::bold;print(omega,"gold                    )= 0xFFD700, style is imba\n"); // rgb(255,215,0)
        omega=fg(fmt::color::golden_rod              )|fmt::emphasis::bold;print(omega,"golden_rod              )= 0xDAA520, style is imba\n"); // rgb(218,165,32)
        omega=fg(fmt::color::gray                    )|fmt::emphasis::bold;print(omega,"gray                    )= 0x808080, style is imba\n"); // rgb(128,128,128)
        omega=fg(fmt::color::green                   )|fmt::emphasis::bold;print(omega,"green                   )= 0x008000, style is imba\n"); // rgb(0,128,0)
        omega=fg(fmt::color::green_yellow            )|fmt::emphasis::bold;print(omega,"green_yellow            )= 0xADFF2F, style is imba\n"); // rgb(173,255,47)
        omega=fg(fmt::color::honey_dew               )|fmt::emphasis::bold;print(omega,"honey_dew               )= 0xF0FFF0, style is imba\n"); // rgb(240,255,240)
        omega=fg(fmt::color::hot_pink                )|fmt::emphasis::bold;print(omega,"hot_pink                )= 0xFF69B4, style is imba\n"); // rgb(255,105,180)
        omega=fg(fmt::color::indian_red              )|fmt::emphasis::bold;print(omega,"indian_red              )= 0xCD5C5C, style is imba\n"); // rgb(205,92,92)
        omega=fg(fmt::color::indigo                  )|fmt::emphasis::bold;print(omega,"indigo                  )= 0x4B0082, style is imba\n"); // rgb(75,0,130)
        omega=fg(fmt::color::ivory                   )|fmt::emphasis::bold;print(omega,"ivory                   )= 0xFFFFF0, style is imba\n"); // rgb(255,255,240)
        omega=fg(fmt::color::khaki                   )|fmt::emphasis::bold;print(omega,"khaki                   )= 0xF0E68C, style is imba\n"); // rgb(240,230,140)
        omega=fg(fmt::color::lavender                )|fmt::emphasis::bold;print(omega,"lavender                )= 0xE6E6FA, style is imba\n"); // rgb(230,230,250)
        omega=fg(fmt::color::lavender_blush          )|fmt::emphasis::bold;print(omega,"lavender_blush          )= 0xFFF0F5, style is imba\n"); // rgb(255,240,245)
        omega=fg(fmt::color::lawn_green              )|fmt::emphasis::bold;print(omega,"lawn_green              )= 0x7CFC00, style is imba\n"); // rgb(124,252,0)
        omega=fg(fmt::color::lemon_chiffon           )|fmt::emphasis::bold;print(omega,"lemon_chiffon           )= 0xFFFACD, style is imba\n"); // rgb(255,250,205)
        omega=fg(fmt::color::light_blue              )|fmt::emphasis::bold;print(omega,"light_blue              )= 0xADD8E6, style is imba\n"); // rgb(173,216,230)
        omega=fg(fmt::color::light_coral             )|fmt::emphasis::bold;print(omega,"light_coral             )= 0xF08080, style is imba\n"); // rgb(240,128,128)
        omega=fg(fmt::color::light_cyan              )|fmt::emphasis::bold;print(omega,"light_cyan              )= 0xE0FFFF, style is imba\n"); // rgb(224,255,255)
        omega=fg(fmt::color::light_golden_rod_yellow )|fmt::emphasis::bold;print(omega,"light_golden_rod_yellow )= 0xFAFAD2, style is imba\n"); // rgb(250,250,210)
        omega=fg(fmt::color::light_gray              )|fmt::emphasis::bold;print(omega,"light_gray              )= 0xD3D3D3, style is imba\n"); // rgb(211,211,211)
        omega=fg(fmt::color::light_green             )|fmt::emphasis::bold;print(omega,"light_green             )= 0x90EE90, style is imba\n"); // rgb(144,238,144)
        omega=fg(fmt::color::light_pink              )|fmt::emphasis::bold;print(omega,"light_pink              )= 0xFFB6C1, style is imba\n"); // rgb(255,182,193)
        omega=fg(fmt::color::light_salmon            )|fmt::emphasis::bold;print(omega,"light_salmon            )= 0xFFA07A, style is imba\n"); // rgb(255,160,122)
        omega=fg(fmt::color::light_sea_green         )|fmt::emphasis::bold;print(omega,"light_sea_green         )= 0x20B2AA, style is imba\n"); // rgb(32,178,170)
        omega=fg(fmt::color::light_sky_blue          )|fmt::emphasis::bold;print(omega,"light_sky_blue          )= 0x87CEFA, style is imba\n"); // rgb(135,206,250)
        omega=fg(fmt::color::light_slate_gray        )|fmt::emphasis::bold;print(omega,"light_slate_gray        )= 0x778899, style is imba\n"); // rgb(119,136,153)
        omega=fg(fmt::color::light_steel_blue        )|fmt::emphasis::bold;print(omega,"light_steel_blue        )= 0xB0C4DE, style is imba\n"); // rgb(176,196,222)
        omega=fg(fmt::color::light_yellow            )|fmt::emphasis::bold;print(omega,"light_yellow            )= 0xFFFFE0, style is imba\n"); // rgb(255,255,224)
        omega=fg(fmt::color::lime                    )|fmt::emphasis::bold;print(omega,"lime                    )= 0x00FF00, style is imba\n"); // rgb(0,255,0)
        omega=fg(fmt::color::lime_green              )|fmt::emphasis::bold;print(omega,"lime_green              )= 0x32CD32, style is imba\n"); // rgb(50,205,50)
        omega=fg(fmt::color::linen                   )|fmt::emphasis::bold;print(omega,"linen                   )= 0xFAF0E6, style is imba\n"); // rgb(250,240,230)
        omega=fg(fmt::color::magenta                 )|fmt::emphasis::bold;print(omega,"magenta                 )= 0xFF00FF, style is imba\n"); // rgb(255,0,255)
        omega=fg(fmt::color::maroon                  )|fmt::emphasis::bold;print(omega,"maroon                  )= 0x800000, style is imba\n"); // rgb(128,0,0)
        omega=fg(fmt::color::medium_aquamarine       )|fmt::emphasis::bold;print(omega,"medium_aquamarine       )= 0x66CDAA, style is imba\n"); // rgb(102,205,170)
        omega=fg(fmt::color::medium_blue             )|fmt::emphasis::bold;print(omega,"medium_blue             )= 0x0000CD, style is imba\n"); // rgb(0,0,205)
        omega=fg(fmt::color::medium_orchid           )|fmt::emphasis::bold;print(omega,"medium_orchid           )= 0xBA55D3, style is imba\n"); // rgb(186,85,211)
        omega=fg(fmt::color::medium_purple           )|fmt::emphasis::bold;print(omega,"medium_purple           )= 0x9370DB, style is imba\n"); // rgb(147,112,219)
        omega=fg(fmt::color::medium_sea_green        )|fmt::emphasis::bold;print(omega,"medium_sea_green        )= 0x3CB371, style is imba\n"); // rgb(60,179,113)
        omega=fg(fmt::color::medium_slate_blue       )|fmt::emphasis::bold;print(omega,"medium_slate_blue       )= 0x7B68EE, style is imba\n"); // rgb(123,104,238)
        omega=fg(fmt::color::medium_spring_green     )|fmt::emphasis::bold;print(omega,"medium_spring_green     )= 0x00FA9A, style is imba\n"); // rgb(0,250,154)
        omega=fg(fmt::color::medium_turquoise        )|fmt::emphasis::bold;print(omega,"medium_turquoise        )= 0x48D1CC, style is imba\n"); // rgb(72,209,204) = 0xF0F8FF,  // rgb(240,248,255)
        omega=fg(fmt::color::medium_violet_red       )|fmt::emphasis::bold;print(omega,"medium_violet_red       )= 0xC71585, style is imba\n"); // rgb(199,21,133)
        omega=fg(fmt::color::midnight_blue           )|fmt::emphasis::bold;print(omega,"midnight_blue           )= 0x191970, style is imba\n"); // rgb(25,25,112)
        omega=fg(fmt::color::mint_cream              )|fmt::emphasis::bold;print(omega,"mint_cream              )= 0xF5FFFA, style is imba\n"); // rgb(245,255,250)
        omega=fg(fmt::color::misty_rose              )|fmt::emphasis::bold;print(omega,"misty_rose              )= 0xFFE4E1, style is imba\n"); // rgb(255,228,225)
        omega=fg(fmt::color::moccasin                )|fmt::emphasis::bold;print(omega,"moccasin                )= 0xFFE4B5, style is imba\n"); // rgb(255,228,181)
        omega=fg(fmt::color::navajo_white            )|fmt::emphasis::bold;print(omega,"navajo_white            )= 0xFFDEAD, style is imba\n"); // rgb(255,222,173)
        omega=fg(fmt::color::navy                    )|fmt::emphasis::bold;print(omega,"navy                    )= 0x000080, style is imba\n"); // rgb(0,0,128)
        omega=fg(fmt::color::old_lace                )|fmt::emphasis::bold;print(omega,"old_lace                )= 0xFDF5E6, style is imba\n"); // rgb(253,245,230)
        omega=fg(fmt::color::olive                   )|fmt::emphasis::bold;print(omega,"olive                   )= 0x808000, style is imba\n"); // rgb(128,128,0)
        omega=fg(fmt::color::olive_drab              )|fmt::emphasis::bold;print(omega,"olive_drab              )= 0x6B8E23, style is imba\n"); // rgb(107,142,35)
        omega=fg(fmt::color::orange                  )|fmt::emphasis::bold;print(omega,"orange                  )= 0xFFA500, style is imba\n"); // rgb(255,165,0)
        omega=fg(fmt::color::orange_red              )|fmt::emphasis::bold;print(omega,"orange_red              )= 0xFF4500, style is imba\n"); // rgb(255,69,0)
        omega=fg(fmt::color::orchid                  )|fmt::emphasis::bold;print(omega,"orchid                  )= 0xDA70D6, style is imba\n"); // rgb(218,112,214)
        omega=fg(fmt::color::pale_golden_rod         )|fmt::emphasis::bold;print(omega,"pale_golden_rod         )= 0xEEE8AA, style is imba\n"); // rgb(238,232,170)
        omega=fg(fmt::color::pale_green              )|fmt::emphasis::bold;print(omega,"pale_green              )= 0x98FB98, style is imba\n"); // rgb(152,251,152)
        omega=fg(fmt::color::pale_turquoise          )|fmt::emphasis::bold;print(omega,"pale_turquoise          )= 0xAFEEEE, style is imba\n"); // rgb(175,238,238)
        omega=fg(fmt::color::pale_violet_red         )|fmt::emphasis::bold;print(omega,"pale_violet_red         )= 0xDB7093, style is imba\n"); // rgb(219,112,147)
        omega=fg(fmt::color::papaya_whip             )|fmt::emphasis::bold;print(omega,"papaya_whip             )= 0xFFEFD5, style is imba\n"); // rgb(255,239,213)
        omega=fg(fmt::color::peach_puff              )|fmt::emphasis::bold;print(omega,"peach_puff              )= 0xFFDAB9, style is imba\n"); // rgb(255,218,185)
        omega=fg(fmt::color::peru                    )|fmt::emphasis::bold;print(omega,"peru                    )= 0xCD853F, style is imba\n"); // rgb(205,133,63)
        omega=fg(fmt::color::pink                    )|fmt::emphasis::bold;print(omega,"pink                    )= 0xFFC0CB, style is imba\n"); // rgb(255,192,203)
        omega=fg(fmt::color::plum                    )|fmt::emphasis::bold;print(omega,"plum                    )= 0xDDA0DD, style is imba\n"); // rgb(221,160,221)
        omega=fg(fmt::color::powder_blue             )|fmt::emphasis::bold;print(omega,"powder_blue             )= 0xB0E0E6, style is imba\n"); // rgb(176,224,230)
        omega=fg(fmt::color::purple                  )|fmt::emphasis::bold;print(omega,"purple                  )= 0x800080, style is imba\n"); // rgb(128,0,128)
        omega=fg(fmt::color::rebecca_purple          )|fmt::emphasis::bold;print(omega,"rebecca_purple          )= 0x663399, style is imba\n"); // rgb(102,51,153)
        omega=fg(fmt::color::red                     )|fmt::emphasis::bold;print(omega,"red                     )= 0xFF0000, style is imba\n"); // rgb(255,0,0)
        omega=fg(fmt::color::rosy_brown              )|fmt::emphasis::bold;print(omega,"rosy_brown              )= 0xBC8F8F, style is imba\n"); // rgb(188,143,143)
        omega=fg(fmt::color::royal_blue              )|fmt::emphasis::bold;print(omega,"royal_blue              )= 0x4169E1, style is imba\n"); // rgb(65,105,225)
        omega=fg(fmt::color::saddle_brown            )|fmt::emphasis::bold;print(omega,"saddle_brown            )= 0x8B4513, style is imba\n"); // rgb(139,69,19)
        omega=fg(fmt::color::salmon                  )|fmt::emphasis::bold;print(omega,"salmon                  )= 0xFA8072, style is imba\n"); // rgb(250,128,114)
        omega=fg(fmt::color::sandy_brown             )|fmt::emphasis::bold;print(omega,"sandy_brown             )= 0xF4A460, style is imba\n"); // rgb(244,164,96)
        omega=fg(fmt::color::sea_green               )|fmt::emphasis::bold;print(omega,"sea_green               )= 0x2E8B57, style is imba\n"); // rgb(46,139,87)
        omega=fg(fmt::color::sea_shell               )|fmt::emphasis::bold;print(omega,"sea_shell               )= 0xFFF5EE, style is imba\n"); // rgb(255,245,238)
        omega=fg(fmt::color::sienna                  )|fmt::emphasis::bold;print(omega,"sienna                  )= 0xA0522D, style is imba\n"); // rgb(160,82,45)
        omega=fg(fmt::color::silver                  )|fmt::emphasis::bold;print(omega,"silver                  )= 0xC0C0C0, style is imba\n"); // rgb(192,192,192)
        omega=fg(fmt::color::sky_blue                )|fmt::emphasis::bold;print(omega,"sky_blue                )= 0x87CEEB, style is imba\n"); // rgb(135,206,235)
        omega=fg(fmt::color::slate_blue              )|fmt::emphasis::bold;print(omega,"slate_blue              )= 0x6A5ACD, style is imba\n"); // rgb(106,90,205)
        omega=fg(fmt::color::slate_gray              )|fmt::emphasis::bold;print(omega,"slate_gray              )= 0x708090, style is imba\n"); // rgb(112,128,144)
        omega=fg(fmt::color::snow                    )|fmt::emphasis::bold;print(omega,"snow                    )= 0xFFFAFA, style is imba\n"); // rgb(255,250,250)
        omega=fg(fmt::color::spring_green            )|fmt::emphasis::bold;print(omega,"spring_green            )= 0x00FF7F, style is imba\n"); // rgb(0,255,127)
        omega=fg(fmt::color::steel_blue              )|fmt::emphasis::bold;print(omega,"steel_blue              )= 0x4682B4, style is imba\n"); // rgb(70,130,180)
        omega=fg(fmt::color::tan                     )|fmt::emphasis::bold;print(omega,"tan                     )= 0xD2B48C, style is imba\n"); // rgb(210,180,140)
        omega=fg(fmt::color::teal                    )|fmt::emphasis::bold;print(omega,"teal                    )= 0x008080, style is imba\n"); // rgb(0,128,128)
        omega=fg(fmt::color::thistle                 )|fmt::emphasis::bold;print(omega,"thistle                 )= 0xD8BFD8, style is imba\n"); // rgb(216,191,216)
        omega=fg(fmt::color::tomato                  )|fmt::emphasis::bold;print(omega,"tomato                  )= 0xFF6347, style is imba\n"); // rgb(255,99,71)
        omega=fg(fmt::color::turquoise               )|fmt::emphasis::bold;print(omega,"turquoise               )= 0x40E0D0, style is imba\n"); // rgb(64,224,208)
        omega=fg(fmt::color::violet                  )|fmt::emphasis::bold;print(omega,"violet                  )= 0xEE82EE, style is imba\n"); // rgb(238,130,238)
        omega=fg(fmt::color::wheat                   )|fmt::emphasis::bold;print(omega,"wheat                   )= 0xF5DEB3, style is imba\n"); // rgb(245,222,179)
        omega=fg(fmt::color::white                   )|fmt::emphasis::bold;print(omega,"white                   )= 0xFFFFFF, style is imba\n"); // rgb(255,255,255)
        omega=fg(fmt::color::white_smoke             )|fmt::emphasis::bold;print(omega,"white_smoke             )= 0xF5F5F5, style is imba\n"); // rgb(245,245,245)
        omega=fg(fmt::color::yellow                  )|fmt::emphasis::bold;print(omega,"yellow                  )= 0xFFFF00, style is imba\n"); // rgb(255,255,0)
        omega=fg(fmt::color::yellow_green            )|fmt::emphasis::bold;print(omega,"yellow_green            )= 0x9ACD32  style is imba\n"); // rgb(154,205,50)
}
