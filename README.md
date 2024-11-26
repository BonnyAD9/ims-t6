# IMS T6: Komunikace a služby

Project to the subject IMS (modeling and simulation).

## How to install simlib for dummies:
- Download simlib [here](https://www.fit.vut.cz/person/peringer/public/SIMLIB/source/).
- Then do:
```sh
tar xzf <simlib-file>
cd simlib
make
sudo make install
printf /usr/local/lib | sudo cat /etc/ld.so.conf.d/simlib.conf
```
- Restart vscode
