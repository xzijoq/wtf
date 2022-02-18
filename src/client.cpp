#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <asio/error.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <asio/ip/basic_endpoint.hpp>
#include <chrono>
#include <cstdint>
#include <system_error>
#include <thread>

#include "defs.h"
#include "main.h"
#include "style.h"

#pragma region using
using fmt::print;
using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;
using ull = unsigned long long;
using namespace asio;
using asio::ip::tcp;
using namespace std::placeholders;
#pragma endregion

void writeToTcpSocket( tcp::socket& soc );
int  main( int argc, char* argv[] )
{
    print( orStyle, "\nCLIENT STARTS HERE\n" );
    cout << nanoseconds( 2s ).count();
    error_code ec;
    io_context ioc;

    //! Client local
    string ClientIPstring = "127.1.12.1";
    if ( argc > 1 ) { ClientIPstring = "127.1.12." + string( argv[1] ); }
    constexpr uint16_t ClientPort = 1336;
    tcp::endpoint      ClientEndpoint{ ip::make_address( ClientIPstring, ec ),
                                  ClientPort };
    checkec( ec, where );

    //! Server Remote
    const string       ServerIPstring = "127.1.0.0";
    constexpr uint16_t ServerPort     = 1338;
    tcp::endpoint      ServerEndPoint{ ip::make_address( ServerIPstring, ec ),
                                  ServerPort };
    checkec( ec, where );

    auto protocol = tcp::v4();

    //! Buffers
    string       inputbuf = "                          ";
    string const outbuf   = "FuckYou";
    auto         inb      = buffer( inputbuf, sizeof( inputbuf ) );
    auto         oub      = buffer( outbuf, sizeof( outbuf ) );


   // &b=c;

    //! Socket Stuff
    tcp::socket soc( ioc );

    soc.open( protocol, ec );
    checkec( ec, where );

    soc.set_option( socket_base::reuse_address( true ), ec );
    checkec( ec, where );

    soc.bind( ClientEndpoint, ec );
    checkec( ec, where );

    soc.connect( ServerEndPoint, ec );
    checkec( ec, where, "connection to server" );

    //auto wb = soc.write_some( oub, ec );
     //checkec( ec, where );

    writeToTcpSocket( soc );

    auto rb = soc.read_some( inb, ec );
    checkec( ec, where );

    print( liStyle, "\nServerSays: {}", inputbuf );

    print( orStyle, "\nCLIENT ENDS HERE\n" );
    return 0;
}

// !todo how to bind client to a specific port without specifying the protocol,
// which can be determined by asio::connect

#pragma region doom
const string   doom = R"fuckyou(From Wikipedia, the free encyclopedia
Jump to navigation
Jump to search
This article is about the franchise. For other uses, see Doom.
Doom
Doom – Game’s logo.svg
Lettering since Doom (2016)
Created by	

    John Carmack
    John Romero
    Adrian Carmack
    Kevin Cloud
    Tom Hall

Original work	Doom (1993)
Owner	Id Software
(ZeniMax Media)
(Microsoft)
Print publications
Novel(s)	Novel Series
Comics	Doom (1996)
Films and television
Film(s)	Doom (2005)
Doom: Annihilation (2019)
Games
Traditional	Doom: The Boardgame (2004)
Video game(s)	List of video games

Doom (stylized as DooM, and later DOOM) is a video game series and media franchise created by John Carmack, John Romero, Adrian Carmack, Kevin Cloud, and Tom Hall.[1] The series focuses on the exploits of an unnamed space marine operating under the auspices of the Union Aerospace Corporation (UAC), who fights hordes of demons and the undead in order to save Earth from an apocalyptic invasion.

The original 1993 Doom is considered one of the pioneering first-person shooter games, introducing to IBM-compatible computers features such as 3D graphics, third-dimension spatiality, networked multiplayer gameplay, and support for player-created modifications with the Doom WAD format. Over 10 million copies of games in the Doom series have been sold; the series has spawned numerous sequels, novels, comic books, board games, and film adaptations.
Contents

    1 Overview
    2 Development and history
        2.1 Classic series (1993–1997)
        2.2 Doom 3 and mobile spin-offs (2004–2012)
        2.3 Rebooted series (2016–present)
        2.4 Future
    3 Games
        3.1 Main series
        3.2 Spin-offs
    4 Other media
        4.1 Novels
        4.2 Comic book
        4.3 Tabletop games
        4.4 Films
            4.4.1 Doom (2005)
            4.4.2 Doom: Annihilation (2019)
    5 Reception
        5.1 Sales
    6 References

Overview

The Doom video games consist of first-person shooters in which the player controls an unnamed space marine commonly referred to as Doomguy by fans (in the 2016 series, the protagonist is called the "Doom Slayer" or just "Slayer"). The player battles the forces of Hell, consisting of demons and the undead. The games are usually set within sprawling bases on Mars or its moons, while some parts take place in Hell itself. The classic series had only a limited focus on the story, much of which was present in the manuals rather than the games themselves.[2] More recent titles, particularly the 2016 series, would feature a heavier focus on narrative.[3]

The original game featured a total of eight weapons, designed in such a way that no weapon became obsolete after the acquisition of another. With the player carrying all of these weapons at once, the strategy of "gun juggling"- rapidly switching between the weapons depending on circumstance- can be employed.[4] Outside of combat mechanics, Doom levels often feature mazes, coloured key cards and hidden areas.[5][6] Due to technical limitations, the player could not jump or look up and down in the classic series. These features were added in newer titles.[7]
Development and history
Release timeline
Main series in bold
1993	Doom
1994	Doom II: Hell on Earth
1995	Master Levels for Doom II
The Ultimate Doom
1996	Final Doom
1997	Doom 64
1998
1999
2000
2001
2002
2003
2004	Doom 3
2005	Doom 3: Resurrection of Evil
Doom RPG
2006
2007
2008
2009	Doom Resurrection
Doom II RPG
2010	Doom II: No Rest for the Living
2011
2012	Doom 3: BFG Edition
2013
2014
2015
2016	Doom
2017	Doom VFR
2018
2019	Sigil
2020	Doom Eternal
Doom 64: The Lost Levels
The Ancient Gods, Part One
2021	The Ancient Gods, Part Two
TBA	Sigil 2
Classic series (1993–1997)
See also: Development of Doom

The development of the original Doom started in 1992, when John Carmack developed a new game engine, the Doom engine, while the rest of the id Software team finished the Wolfenstein 3D prequel, Spear of Destiny. The game launched in an episodic format in 1993- with the first episode available as shareware and two more episodes available by mail order. The first episode was largely designed by John Romero.[8] The title proved extremely popular, with the full version of the game selling one million copies. The term "Doom clone" became the name for new genre now known as first person shooters for several years.[9]

Doom II: Hell on Earth was released in 1994 exclusively in a commercial format. Only minor changes were made at a technical level; the game however featured new enemies, a new "Super Shotgun" weapon, and more complex levels.[10] The game was followed by an expansion in 1995, entitled Master Levels for Doom II, which added 20 additional levels. A fourth episode was added to the original game by the 1995 re-release.[11]

From 1995 id Software were focused on the development of the new Quake trilogy, which would be developed by the company throughout the late 1990s.[12] However, two additional games would be released over the following years, largely developed by third party groups under id's supervision. The first of these was Final Doom, which featured 64 levels based on the Doom II engine, organised into two episodes. TNT: Evilution was developed by the modding group TeamTNT and completed in November 1995, while the second episode The Plutonia Experiment was developed by TNT's Dario and Milo Casali and completed in January 1996.

Midway Games developed Doom 64 under id supervision for release in 1997. The title featured a new engine, with larger sprites and higher quality textures. The technical changes allowed for greater flexibility with level design, such as the ability to adjust the geometry of the map during play. Id did not allow the title to be called Doom 3, as the name was being reserved for a potential return to the franchise after the development of Quake.[13][14]
Doom 3 and mobile spin-offs (2004–2012)
Main article: Doom 3 § Production

Doom 3 was announced in 2000, marking id Software's return to the franchise after the release of Quake III Arena. The troubled development of Quake had resulted in major staffing changes at id, with a number of key figures from the mid 90s having departed. This included the original designer John Romero, who was fired in 1996.[8] In the interim, the company had also hired former Doom modder Tim Willits.[12]

Despite the title, Doom 3 was planned as a remake of the original game, a prospect which caused some internal disagreements among the developers. The design of the title would be led by Willits.[15] Using the new id tech 4 engine, numerous technical improvements were made over the classic series, allowing greater realism and interactivity. The game used voice acting and featured a greater focus on narrative than earlier titles. A demo of the game was shown at E3 2002 and was subsequently leaked online, well ahead of the 2004 release date. At the time, it was the first Doom title in seven years, and helped renew interest in the franchise.[16] An expansion, Doom 3: Resurrection of Evil was released in 2005. Unlike the base game, the expansion was developed by Nerve Software. A 2012 "BFG Edition" featured both previous releases along with a new expansion entitled The Lost Mission.

Doom 4 hints were present in 2007 at QuakeCon, and the game was formally announced in 2008. Response to preview material was negative, with fans nicknaming the project "Call of Doom", after a perceived similarity to the Call of Duty franchise. Bethesda marketing vice president Pete Hines stated in retrospect that "it wasn't Doom enough". The game would never be released, with Bethesda cancelling the project in 2013. John Carmack, one of the few remaining veterans from the development of the classic series still present at id, left the studio in November.[17]

The period also saw the release of several spinoffs for mobile platforms. These included Doom RPG (2005), Doom II RPG (2009), and Doom Resurrection (2009). Additionally, the 2010 Xbox Live Arcade re-release of Doom II featured a new expansion entitled No Rest for the Living, which was developed by Nerve Software. This was structured in a similar manner to classic Doom chapters, with eight primary levels and one secret level. This release was also packaged with the BFG Edition of Doom 3 in 2012.[18][19]
Rebooted series (2016–present)

After the 2013 scrapping of the Doom 4 project, Willits stated that the next game in the Doom series was still the team's focus.[20] Hugo Martin was hired as creative director on the project in 2013.[21] The project was announced simply as Doom in 2014, and was released to generally positive reception in 2016. A glory kill mechanic and additional platforming manoeuvres were among the main gameplay additions.[22] The game's multiplayer mode received three small DLC releases over the course of the first year, and all three were then released for free with the 6.66 update on July 19, 2017.[23]

The 2016 series was not originally described as a continuation or origin story of earlier games, however plot details in the sequel Doom Eternal and commentary from Martin would later describe it as a continuation of the classic series.[24][25] The 2020 re-release of Doom 64 included an expansion entitled The Lost Levels, intended "to connect “old” Doom to “new” Doom".[26]

A VR spinoff entitled Doom VFR was released in 2017 to generally positive reception, with reviewers discussing the movement controls in particular- which were well made albeit hidden behind menus. The game featured a single player campaign, and reused enemies and other assets from the 2016 game.[27] The game would be the last Doom title under Willits' leadership, ahead of his departure in 2019.[28] 2018 marked the 25th anniversary of the franchise, and saw The Doom Slayer included as a playable character in id Software's Quake Champions. That year, John Romero also announced Sigil, an unofficial "fifth episode" of the original 1993 game. The episode was released for free via Romero's website in 2019, with a paid version available that included a soundtrack by Buckethead.[29] While Sigil was developed independently, Bethesda added the episode to the console ports of Doom as a free patch in October, alongside the two chapters of Final Doom.[30][31]

The next main entry in the franchise, Doom Eternal, was directed by Hugo Martin and released in 2020.[32] The title sold very well, generating $450 million in revenue over the first year; double the launch revenue of the previous title. Some commentators cited the timing of the release, which coincided with a wave of interest in gaming worldwide amid restrictions on social gathering during the coronavirus pandemic.[33][34] The game was made in id Tech 7, which afforded numerous technical improvements over the id Tech 6 engine used by its predecessor.[35] An expansion of the game, The Ancient Gods, was released in two parts, one in October 2020 and the other in March 2021.
Future

In March 2021, Hugo Martin discussed some directions future Doom titles could take, discussing time travel or a game set in the time span between Doom 64 and Doom (2016), when the Doom Slayer “first came to that place with the Sentinels, almost like a more medieval setting”.[36][37] Romero confirmed in August 2021 that a second Sigil expansion using the Doom II engine was in development.[38]
Games
Main series
Title 	Details
Doom

Original release date:

    NA: December 10, 1993
    EU: December 1993

	Release years by system:

    1993 – MS-DOS
    1994 – Sega 32X, Atari Jaguar
    1995 – Super Nintendo Entertainment System, PlayStation
    1996 – 3DO
    1997 – Sega Saturn
    1998 – Acorn Archimedes
    2001 – Game Boy Advance
    2006 – Xbox 360 (original Activision release)
    2009 – iOS
    2012 – Xbox 360 (Bethesda re-release)
    2019 – Nintendo Switch, PlayStation 4, Xbox One, Android

Notes:

    Originally developed by id Software and published by GT Interactive Software.
    On April 30, 1995, an updated version of the game, The Ultimate Doom, was released; it included a new fourth episode, "Thy Flesh Consumed", in addition to the original three episodes.
    On December 23, 1997, John Carmack released the source code of Doom for Linux under a proprietary Doom Source License.
    On October 3, 1999, John Carmack relicensed the source code of Doom for Linux to GNU GPL-2.0-or-later. Since then the list of Doom ports has grown from game consoles and operating systems that never saw an official release (including some pre-Android and pre-iOS early smart phones), to unusual devices such as oscilloscopes and other embedded systems.
    On November 3, 2009, John Carmack released the source code of Doom on iOS under GNU GPL-2.0-or-later.
    On May 22, 2019, John Romero released an unofficial 5th episode titled "Sigil" to commemorate the game's 25th anniversary.
    On July 14, 2020, Randal Linden released the source code of Doom on SNES under GNU GPL-3.0-or-later.[39]

Doom II: Hell on Earth

Original release date:

    WW: October 10, 1994

	Release years by system:

    1994 – MS-DOS
    1995 – Mac OS
    2002 – Game Boy Advance
    2010 – Xbox 360 (original Activision release)
    2012 – Xbox 360 (Bethesda re-release)
    2019 – Nintendo Switch, PlayStation 4, Xbox One, iOS, Android

Notes:

    Originally developed by id Software and published by GT Interactive Software.
    On December 26, 1995, an expansion pack, Master Levels for Doom II, was released; it included 21 additional levels.
    On May 26, 2010, an expansion pack, Doom II: No Rest for the Living, was released for the Xbox 360 release of the game, developed by Nerve Software.


Doom 3

Original release dates:

    NA: August 3, 2004
    EU: August 13, 2004

	Release years by system:

    2004 – Microsoft Windows, Linux
    2005 – OS X, Xbox

Notes:

    Originally developed by id Software and published by Activision.
    The Xbox version contains the full versions of The Ultimate Doom and Doom II, but they are only available in the limited collector's edition.
    On November 22, 2011, id Software released the source code under GNU GPL-3.0-or-later.

Doom 3: Resurrection of Evil

Original release dates:

    NA: April 3, 2005
    EU: April 8, 2005

	Release years by system:
2005 – Microsoft Windows, Linux, Xbox
Notes:

    Developed by Nerve Software and published by Activision.
    Expansion pack for Doom 3, which requires Doom 3 to play on Microsoft Windows.
    The Xbox version does not require Doom 3 to play and also contains the full versions of The Ultimate Doom, Doom II, and Master Levels for Doom II.

Doom 3: BFG Edition

Original release dates:

    NA: October 16, 2012
    AU: October 18, 2012
    EU: October 19, 2012

	Release years by system:

    2012 – Microsoft Windows, PlayStation 3, Xbox 360
    2015 – Nvidia Shield
    2019 – Nintendo Switch, PlayStation 4, Xbox One

Notes:

    Originally developed by id Software and published by Bethesda Softworks.
    HD remasters of Doom 3 and its expansion Resurrection of Evil. A new expansion pack is also included in the game titled The Lost Mission.
    The game also includes the full versions of The Ultimate Doom and Doom II, as well as the No Rest for the Living expansion pack by Nerve Software.
    On November 26, 2012, id Software released the source code under GNU GPL-3.0-or-later.

Doom

Original release date:

    WW: May 13, 2016

	Release years by system:

    2016 – Microsoft Windows, PlayStation 4, Xbox One
    2017 – Nintendo Switch
    2020 – Stadia

Notes:

    Developed by id Software and published by Bethesda Softworks.
    Multiplayer co-developed with Certain Affinity.
    SnapMap co-developed with Escalation Studios.

Doom Eternal

Original release date:

    WW: March 20, 2020

	Release years by system:

    2020 – Microsoft Windows, Nintendo Switch, PlayStation 4, Stadia, Xbox One
    2021 – PlayStation 5, Xbox Series X/S

Notes:

    Developed by id Software and published by Bethesda Softworks.
    Sequel to the 2016 reboot.

Spin-offs
Title 	Details
Final Doom

Original release date:

    NA: June 17, 1996
    EU: 1996

	Release years by system:

    1996 – MS-DOS, PlayStation, Mac OS
    2020 – Nintendo Switch, PlayStation 4, Xbox One (as a free add-on for Doom II)[40]

Notes:

    Developed by TeamTNT and published originally by id Software.
    Final Doom is a compilation of two standalone Doom II modifications, TNT: Evilution and The Plutonia Experiment, which include full sets of new levels (both of them use the same level structure as Doom II with 30 regular levels and two secret levels), new graphics and textures, new music (for TNT: Evilution), and new text interlude screens in addition to most of the resources from Doom II and some from Doom.

Doom 64

Original release dates:

    NA: March 31, 1997
    PAL: December 2, 1997

	Release years by system:

    1997 – Nintendo 64
    2020 – Microsoft Windows, Nintendo Switch, PlayStation 4, Stadia, Xbox One (Bethesda re-release)

Notes:

    Originally developed and published by Midway Games.
    The 2020 port is higher-resolution than the original, and includes a new multi-level sequel chapter.[41]

Doom RPG

Original release date:

    WW: September 13, 2005

	Release years by system:
2005 – mobile
Notes:

    Developed by Fountainhead Entertainment and published by JAMDAT Mobile.
    Released for BREW and Java ME

Doom Resurrection

Original release date:

    WW: June 26, 2009

	Release years by system:
2009 – iOS
Notes:

    Developed by Escalation Studios and published by id Software.
    Set in parallel to Doom 3.

Doom II RPG

Original release date:

    WW: November 23, 2009

	Release years by system:

    2009 – Java ME, BlackBerry OS
    2010 – Windows Mobile, iOS

Notes:

    Developed and published by id Software.

Doom VFR

Original release date:

    WW: December 1, 2017

	Release years by system:
2017 – Windows Mixed Reality, HTC Vive, PS VR
Notes:

    Developed by id Software and published by Bethesda Softworks.
    Virtual-reality game, set during the events of Doom (2016).

Other media
Novels
Main article: Doom (novel series)

A set of four novels based on Doom were written by Dafydd ab Hugh and Brad Linaweaver. The books, listed in order, are titled Knee Deep in the Dead, Hell on Earth, Infernal Sky and Endgame. All were published between June 1995 and January 1996 by Pocket Books. The unnamed Marine is called "Flynn Taggart" or "Fly" in the novels. The first two books feature recognizable locations and situations from the first two games.

In 2008, a new series of Doom novels by Matthew J. Costello, an author who had worked on the story and scripts for Doom 3 and Resurrection of Evil, were published. The series of books aim to novelize the story of Doom 3, with the first installment, Worlds on Fire, published on February 26, 2008.[42] The second book in the series, Maelstrom, was released in March 2009.[43]
Comic book

A one-shot comic book written by Steve Behling and Michael Stewart with art by Tom Grindberg was released in May 1996 by Marvel Comics as a giveaway for a video game convention.
Tabletop games

In 2004, a board game designed by Kevin Wilson and published by Fantasy Flight Games titled Doom: The Boardgame was released.[44]

In 2020, Critical Role published a fifth edition Dungeons & Dragons module entitled Doom Eternal: Assault on Amaros Station. The game was written by Christopher Lockey and Matthew Mercer, and received a digital release via the Critical Role store on December 16, 2020.[45][46]
Films
Doom (2005)
Main article: Doom (film)

In 2005, Universal Pictures released the first live-action film adaptation, titled Doom, which starred Karl Urban and Dwayne Johnson.
Doom: Annihilation (2019)
Main article: Doom: Annihilation

In 2019, Universal released a second live-action film adaptation direct-to-video, titled Doom: Annihilation starring Amy Manson.
Reception
Aggregate review scores
As of January 21, 2021. Game 	GameRankings 	Metacritic
Doom (1993) 	(PC) 86.67%[47]
(PS1) 84.00%[48]
(iOS) 82.86%[49]
(X360) 80.16%[50]
(32X) 80.00%[51]
(GBA) 79.87%[52]
(JAG) 78.75%[53]
(SNES) 54.05%[54]
(SAT) 47.00%[55] 	(iOS) 84[56]
(X360) 82[57]
(GBA) 81[58]
Doom II: Hell on Earth 	(PC) 95.00%[59]
(X360) 77.36%[60]
(GBA) 76.64%[61] 	(PC) 83[62]
(X360) 77[63]
(GBA) 77[64]
Final Doom 	(PS1) 80.71%[65]
(MAC) 60.00%[66]
(PC) 56.00%[67] 	—
Doom 64 	(N64) 73.47%[68] 	(XONE) 77[69]
(PS4) 75[70]
(Switch) 77[71]
Doom 3 	(Xbox) 87.63%[72]
(PC) 86.63%[73] 	(Xbox) 88[74]
(PC) 87[75]
Doom 3: Resurrection of Evil 	(PC) 79.52%[76]
(Xbox) 78.02%[77] 	(PC) 78[78]
(Xbox) 77[79]
Doom RPG 	(MOBI) 87.45%[80] 	—
Doom Resurrection 	(iOS) 86.43%[81] 	(iOS) 79[82]
Doom II RPG 	(MOBI) 80.00%[83]
(iOS) 79.00%[84] 	(iOS) 80[85]
Doom 3: BFG Edition 	(PS3) 68.00%[86]
(X360) 66.63%[87]
(PC) 51.67%[88] 	(PS3) 67[89]
(X360) 67[90]
(PC) 59[91]
Doom (2016) 	(XONE) 89.04%[92]
(PS4) 85.82%[93]
(PC) 85.38%[94] 	(XONE) 87[95]
(PS4) 85[96]
(PC) 85[97]
(Switch) 79[98]
Doom Eternal 	— 	(XONE) 88[99]
(PS4) 87[100]
(PC) 88[101]
(Switch) 81[102]

In 1996, Next Generation ranked the series as the 19th top game of all time, for how "despite the hundreds of copycat titles, no one has ever been able to equal id's original, pulsing classic."[103] In 1999, Next Generation listed the Doom series as number 25 on their "Top 50 Games of All Time," commenting that, "despite the graphic advances since Doom was released, the pixilated Barons of Hell and Cyber Demons still rank as some of the scariest things that can grace your screen."[104]

The series' unnamed protagonist, a marine, has had a mostly positive reception. In 2009, GameDaily included "the Marine" on its list of "ten game heroes who fail at the simple stuff" for his inability to look up and down in the original series.[105] UGO Networks ranked him fourth on its 2012 list of best silent protagonists in video games, noting his courage to continue in silence even when he faces Hell's army.[106] In 2013, Complex ranked Doomguy at number 16 on its list of the greatest soldiers in video games for being "the original video game space marine" and "one of the classic silent protagonists."[107] Both CraveOnline and VGRC ranked him the fifth most "badass" male character in the video game's history.[108][109]
Sales

The original Doom sold 3.5 million physical copies[110] and 1.15 million shareware copies[111] from its 1993 release up through 1999. Doom II sold 1.55 million copies of all types in the United States during the same period,[111] with about a quarter of that number also sold in Europe,[112] a total of some 5-6 million sales for the original duology. Doom 3 sold 3.5 million copies along with many copies of the expansion pack Resurrection of Evil from its 2004 release up through 2007, making it the most successful game in the series at that point.[113] The sales of Doom 64 were not disclosed.

The 2016 reboot sold over 2 million copies on the PC alone from its May 2016 release up to July 2017.[114]
References
)fuckyou";

#pragma endregion

void writeToTcpSocket( tcp::socket& soc )
{
    const string toWrite = doom;
    error_code   ec;

    // auto inpbuf=buffer(toWrite);
    int bytesWritten{ 0 };
    while ( bytesWritten < toWrite.size() )
    {
        bytesWritten += soc.write_some(
            buffer( static_cast<const char*>( toWrite.data() ) + bytesWritten,
                    toWrite.size() - bytesWritten ),
            ec );
        checkec( ec, where );
        print( eStyle, "\ndid i wrte: {}", bytesWritten );
    }
}
