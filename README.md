**Forked from:** https://github.com/rigexpert/AntScope2

### Thanks
- [RigExpert](https://rigexpert.com/) and [Andrei Fredd Mironov](https://github.com/andreifreddmironov)
  - For maintaining the official open-source version on GitHub under MIT license.
- D.R. Evans (N7DR) 
  - ... whose blog [Running RigExpert AntScope2 on Debian Stable (buster)](http://drevans.blog.enginehousebooks.com/2020/09/running-rigexpert-antscope2-on-debian.html?m=1) got me through the first time I tried this on LMDE5, without which, I probably would have been dead in the water.


### Context/Backstory
I forked this back during LMDE5. It is in no way official nor am I associated with the creator/team/company. I did finally get the code to compile and have used it a while short 2 issues on LMDE5. Near the end of 2023, I got a new laptop running LMDE6 and realized I had missed a lot of notes trying to get it working before so, this time, I'm intending to try and make this an alternate version for myself. I recently discovered during this that the BLE commit ('b65dcad[...]') will not compile. I tracked it down to dropping of Q_OS_LINUX, but adding that back produced far more issues than before, so there must have been more involved/incompatible changes after the 'improved' commit. 

That said, I'm freezing the AntScope2 part of the code at commit '19323af[...]'. If I have time/need then I may try some future commit past the BLE one, but for now my goal is to make reinstalls a bit easier for myself on LMDE6 frozen at '1932af[...]'. You're welcome to give this a shot as well (and hope it helps) but don't bother with issues/pull requests (I don't have the bandwidth or care for all that too). 

On a related note, '1932af[...]' does use QT5. The newer BLE commit appears to require QT6 (i.e. 'QBluetoothDeviceDiscoveryAgent' wasn't introduced until Qt 6.2 per Qt's docs. An error with that appeared when I 1st tried to compile with QT5. The errors went away on compile attempts with QT6, but the error "Add code for our OS" remained, preventing compile from completing).


### Known Issues
- The 'Frequency=', 'SWR=', etc. overlay box sometimes gets stuck and can't be moved after scan.
    - Workaround: try and move it to where you want it first.
- 'Settings' -> 'General' -> 'Serial port:' dropdown is empty
    - 'Connect analyser' is used anyway, so this hasn't affected functionality for me).
- 'Settings' -> 'General' -> 'Bands highlighting' dropdown is empty empty
    - The `itu-regions.txt` file is likely not being found.
    - Try running program from terminal and see what 'No such file or directory' paths appear in output.
    - Put those files in those locations.
- 'Settings' -> 'Cable' -> 'Change parameters or choose from list...' dropdown is empty
    - `cables.txt` file is likely not being found like above.


### Linux LMDE5/6 Dependencies/Packages
I gave tracking this a go again on LMDE6, but due to the confusion of what was going on with the BLE commit, I ended up just installing everything. Technically, QT6 is also installed on my box, but that shouldn't be necessary. If you discover it is a problem for some reason, then same method will install QT6. Breaking up `sudo` commands so easier to check install list before installing.
- `sudo apt install git` <-- so we can grab this repo.
- `sudo apt install build-essential` <-- usual for about any source compiles.
- `sudo apt install libusb-1.0-0-dev` <-- unsure if this was still needed, but wouldn't doubt it.
- `sudo apt install qt5*`
- `sudo apt install qt*5-dev`
- `sudo apt install libqt5*`
- `sudo apt install qtcreator`
  - This may get pulled in by here. I could not get compile working using CLI so use the IDE. 


### Directory Structure Notes
For source installs/compiles where I'm not using a package manager I like 1 folder that holds everything in my home folder so I know if an app is `make install`ed that I don't accidently blow the folder away later making updates/uninstalls a little less error prone for me. Below is the structure I use for this. If newer to Linux `~` and `$HOME` is synonymous with the user's home directory.
- `~/src_installs`
  - This is where I plonk all my non-package manager installs/compiles.
- `~/src_installs/qt_apps`
  - Qt builds using qtcreator had default directory creation outside of the project root. I'm sure there's good reason for it (I have very little knowlege of Qt), but it spams up my `src_installs` directory, requiring cleanup when I'm done that I'd rather not have to do.
- `~/src_installs/qt_apps/AntScope2_LMDE` <-- Do not create. It will be created on `git clone` step.

### Make Directory Structure and Clone this Repo
1) If not created already: `mkdir ~/src_installs`
2) If not created already: `mkdir ~/src_installs/qt_apps`
3) `cd ~/src_installs/qt_apps`
4) `git clone https://github.com/bmchandler/AntScope2_LMDE.git`
    - This creates the `AntScope2_LMDE` directory under `~/src_installs/qt_apps` used in below steps.


### Compile/Build Steps (as of 240120)
1) Open 'Qt Creator'
2) Click 'Edit' -> 'Preferences'
3) Click 'Kits' section -> 'Qt Versions' tab -> 'Add'
4) In dialog:
    - Nav to `/usr/bin`
    - Select `qmake` (not `qmake6` if it's installed; on LMDE6 `qmake` is QT5)
    - Click 'Open'
5) Click 'Kits' tab under the 'Kits' section
6) Select 'Qt 5.15.8 (qt5)' or equiv. on the 'Qt version' dropdown
7) Click 'OK'
8) Click 'Welcome' -> 'Open Project'
9) Nav to `AntScope2_LMDE` directory
10) Select `AntScope.pro` file and then 'Open'
11) If QT6 is also installed, then 'Configure Project' page may appear. Be sure to uncheck QT6 configuration and check the QT5 one.
12) Let 'Indexing AntScope with clangd' finish along with the other scanning statuses.
13) In bottom left, click Monitor icon-button and then 'Release' under 'Build'
14) Again, let indexing finish.
15) Click the Play icon-button
16) If build succeeds then warnings may appear, but no errors, and AntScope2 program will open (not done yet, but must get here before continuing). I like to close it here.
17) Successful build and run should have created `~/RigExpert/AntScope2` directory. Check and if not then go ahead and create it now with `mkdir ~/RigExpert` and then `mkdir ~/RigExpert/AntScope2`. It will be needed on after build steps.


### After Build Steps
WARNING: Check `post_build_files` TODO has been completed before proceeding (scroll down). If not, then can use D.R. Evans' blog to get the same files if RigExpert has not already provided them in the root project directory.
1) Open terminal/command prompt
2) `cd ~/src_installs/qt_apps/AntScope2_LMDE`
3) Compile should have created `build/release` under project root. If not, then something went wrong or I missed a step at Compile/Build Steps. I think, technically, all that's needed for next part is the green, executable, AntScope2 file (wherever that ended up), and then one can use that directory instead.
4) `mkdir build/release/Resources`
5) `cp post_build_files/cables.txt build/release/Resources/`
6) `cp post_build_files/itu-regions.txt build/release/` (unsure if needed, but I noted back at LMDE5)
7) `cp post_build_files/itu-regions.txt ~/RigExpert/AntScope2/` (from compiled terminal output when missing)
8) `cp itu-regions-defaults.txt build/release/Resources/` (from compiled terminal output when missing)
9) `cp post_build_files/*.qm build/release/`
10) `sudo adduser $USER dialout` (for user access to the hardware when the RigExpert Stick Pro is plugged in)
11) `sudo cp post_build_files/rigexpert-usb.rules /etc/udev/rules.d/`
12) Plug in the Stick Pro w/it's USB cable
13) Run AntScope2 (`~/src_installs/qt_apps/AntScope2_LMDE/build/release/AntScope2`)
14) Click 'Settings' -> 'Connect analyser'
15) Check 'Bands highlighting' dropdown has options. Select your ITU Region.
16) Click 'Cable' tab
17) Check 'Change parameters or choose from list...' dropdown has list of common cables.
18) Click 'Close'
19) If all went well:
    - 'Single' and 'Continuous' under 'Run' should enable.
    - Click 'Single' as a smoke test.
    - If not, then troubleshooting hardware detection is past the scope of this document.


### Add AntScope2 to LMDE's Cinnamon Menu
1) Right-click Cinnamon's Menu/Start button
2) Click 'Edit menu'
3) Select folder you want it under
    - I use 'Hamradio' folder. It's added if you install any of the `hamradio-*` packages from Debian.
4) Click 'New Item'
5) Set:
    - 'Name' = "AntScope2"
    - 'Command' = "/home/{your user dir}/src_installs/qt_apps/AntScope2_LMDE/build/release/AntScope2"
    - 'Comment' = "AntScope2 LMDE build."
    - Icon (via icon button) = `AntScope2.png` (nav to the `~/src_installs/qt_apps/AntScope2` folder)
6) Click 'OK'
7) Click 'Close'
8) Check Menu Button -> 'Hamradio' -> 'AntScope2' appears and executes on click.


### TODOs
- [ ] Add directory to this repo containing the extra files downloaded from D.R. Evans' blog since I have no clue where to get them otherwise. Create folder `post_build_files` to contain all files for below steps.
- [ ] Write an automated script to do more/all of the manual compile, post-build, and menu add steps.
- [ ] Create a .Desktop file for LMDE6 if needed for menu add automation.
