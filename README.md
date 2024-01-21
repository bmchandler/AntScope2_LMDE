**Forked from:** https://github.com/rigexpert/AntScope2

### Thanks
- [RigExpert](https://rigexpert.com/) and [Andrei Fredd Mironov](https://github.com/andreifreddmironov)
  - For maintaining the official open-source version on GitHub under MIT license.
- D.R. Evans (N7DR) 
  - ... whose blog [Running RigExpert AntScope2 on Debian Stable (buster)](http://drevans.blog.enginehousebooks.com/2020/09/running-rigexpert-antscope2-on-debian.html?m=1) got me through the first time I tried this on LMDE5, without which, I probably would have been dead in the water.

### Context/Backstory
I forked this back during LMDE5. It is in no way official nor am I associated with the creator/team/company. I did finally get the code to compile and have used it a while short 2 issues on LMDE5. Near the end of 2023, I got a new laptop running LMDE6 and realized I had missed a lot of notes trying to get it working before so, this time, I'm intending to try and make this an alternate version for myself. I recently discovered during this that the BLE commit ('b65dcad[...]') will not compile. I tracked it down to dropping of Q_OS_LINUX, but adding that back produced far more issues than before, so there must have been more involved/incompatible changes after the 'improved' commit. 

That said, I'm freezing the AntScope2 part of the code at commit '19323af[...]'. If I have time/need then I may try some future commit past the BLE one, but for now my goal is to make reinstalls a bit easier for myself on LMDE6 frozen at '1932af[...]'. You're welcome to give this a shot as well (and hope it helps) but don't bother with issues/pull requests (I don't have the bandwidth or care for all that too). 

On a related note, '1932af[...]' does use QT5. The newer BLE commit appears to require QT6 (i.e. 'QBluetoothDeviceDiscoveryAgent' wasn't introduced until Qt 6.2 per Qt's docs. An error with that appeared when I 1st tried to compile with QT5. The errors went away on compile attempts with QT6, but the error "Add code for our OS" remains, preventing compile from completing).

### Linux LMDE5/6 Dependencies/Packages
I have tracking this a go again on LMDE6, but due to the confusion of what was going on with the BLE commit, I ended up just installing everything. Technically, QT6 is also installed on my box, but that shouldn't be necessary. If you discover so, then same method will install QT6. Breaking up so easier to check install list before 'Y'.
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

### Compile Steps (as of 240120)
1) TODO
