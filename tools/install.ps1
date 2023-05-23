wix build -arch x64 -pdbtype none .\tools\install.wxs -o .\build\test.msi

msiexec /i test.msi /l*v test.log
msiexec /x test.msi /l*v test.log

msiexec /i test.msi
msiexec /x test.msi
