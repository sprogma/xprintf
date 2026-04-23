mkdir -p obj
ls src/*.asm | % { fasm $_ ($o="obj/$($_.Name).o") | oh; $o } | set-variable files
# create library
ld -shared $files -o libxprintf.so

# build tests
gcc test.c -L. -lxprintf -o test.out -g
$env:LD_LIBRARY_PATH="$PSScriptRoot"

# build tests
gcc bench.c -L. -lxprintf -o bench.out -g -Ofast
$env:LD_LIBRARY_PATH="$PSScriptRoot"

./test.out || Write-Host "Tests failed!!! [exit code $LASTEXITCODE]" -Fore red
