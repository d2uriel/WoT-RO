### World of Tanks Replay Organizer by d2uriel ###
Version: 1.1

1. Introduction

    This small application allows you to manage your World of Tanks replays.
    Basic options:
    - basic info about replays,
    - move replays to a specified folder,
    - find and move all Clan Wars replays to a specified folder,
    - add comments to CW replays,
    - group your replays by map, vehicle, etc.,
    - remove incomplete replays.


2. Detailed info

    There's 3 tabs in WoT-RO. First one shows you all replays loaded from WoT
    folder, next one shows replays from favourites folder and the last one
    shows replays from CW folder. I guess that's clear.

    How does the app tell that a replay is from CW? If all members of players
    team are from the same clan and all members of the enemy team are from
    a different clan, but same one within the team, then the app will mark this
    replay as a CW replay. Yes, you are right. If you're gonna play in Team
    Companies with your clan mates and you're gonna end up fighting with
    another clan... well, it's gonna be marked as CW.

    2.1. Settings

        2.1.1 Folders group box

            In this box you can specify folders to use for each specific tab.
            Just click the browse button and pick a correct folder and then
            your replays will be loaded.

        2.1.2 Replay grouping group boxes

            Here you can tell WoT-RO how should it group your favourite
            and CW replays. For example:

            CW grouping is set to: [map]/[clan]
            Example replay: Prokhorovka, enemy clan was DeltaForce

            WoT-RO will create a folder inside your CW replays folder named
            Prokhorovka and inside that a folder named DeltaForce. The
            example replay will be moved there.

        2.1.3 Automatisation options group box

            Auto move new Clan Wars replays - this option will automatically
            move your CW replays to appropriate folders as soon as WoT-RO
            is started.

            Auto resize columns to contents - this option will change column
            width in all tables to fit their contents.

        2.1.4 Other options group box

            Language - you can change the app language here. Simple.

    2.2 Replay menu

        2.2.1 Move selected replays to favourites

            This command will move all selected replays from the current tab
            to favourites folder.

        2.2.2 Move CW replays

            This command moves all replays marked as CW in the WoT folder to
            CW folder.

        2.2.3 Remove all incomplete replays

            This one will remove all incomplete replays from the current tab.
            What's an incomplete replay? If you didn't wait until the end of
            battle then you have an incomplete replay.

        2.2.4 Remove selected replays

            Removes all selected replays from the current tab.


3. Requirements

    1. All DLL's within the archive,
    2. Microsoft Visual Studio Redistributable package is required to run this
       application. You can find it here:
       http://www.microsoft.com/en-us/download/details.aspx?id=5555


4. Known issues

    1. Tank name list sucks - if you know where to get a better one just lemme know.


5. To do list

    // TBD


6. Responsibility & liability

    I take no responsibility for whatever damage to your computer or files this
    piece of software may do. Of course it is intended to work properly but...
    shit happens. All files inside the archive were scanned for viruses before
    uploading and they were clean.


7. Bugs, feature requests, suggestions, comments?

    If you find any bugs, have feature requests, suggestions or comments please
    contact me in-game.


8. Author

    d2uriel (Z0P), EU


9. License

    This software is licensed under LGPL just like Qt framework is.


10. Version history

    v1.1:
        - added multilingual support,
        - minor bug fixes.

    v1.0 - first release.
