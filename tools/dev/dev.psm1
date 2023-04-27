# VS

function Initialize-DevShell64 {
    $vswhere = "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    $vspath = & $vswhere -products * -latest -property installationPath
    & "$vspath\Common7\Tools\Launch-VsDevShell.ps1" -HostArch amd64 -Arch amd64 -SkipAutomaticLocation
}
Set-Alias -Name dev -Value Initialize-DevShell64

function Initialize-DevShell32 {
    $vswhere = "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    $vspath = & $vswhere -products * -latest -property installationPath
    & "$vspath\Common7\Tools\Launch-VsDevShell.ps1" -HostArch x86 -Arch x86 -SkipAutomaticLocation
}
Set-Alias -Name dev32 -Value Initialize-DevShell32

# CMAKE

function Invoke-Generation {
    cmake --preset $args
}
Set-Alias -Name generate -Value Invoke-Generation

function Invoke-Build {
    cmake --build --preset $args
}
Set-Alias -Name build -Value Invoke-Build

function Invoke-Preset {
    cmake --preset $args
    cmake --build --preset $args
}
Set-Alias -Name preset -Value Invoke-Preset

function Watch-CMake {
    $folder = Split-Path $MyInvocation.PSScriptRoot
    $filter = "CMakeLists.txt"
    $notify = [IO.NotifyFilters]::LastWrite
    $change = [IO.WatcherChangeTypes]::Changed
    $timeout = 1000

    try {
        Write-Warning "FileSystemWatcher is monitoring $folder\$filter"
        Write-Warning "Running initial generation..."
        gen_debug
        $watcher = New-Object -TypeName IO.FileSystemWatcher -ArgumentList $folder, $filter -Property @{
            IncludeSubdirectories = $false
            NotifyFilter          = $notify
        }
        while ($true) {
            if ($watcher.WaitForChanged($change, $timeout).TimedOut) { continue }
            gen_debug
        }
    }

    finally {
        $watcher.Dispose()
        Write-Warning "FileSystemWatcher Removed"
        remove
    }
}
Set-Alias -Name watch -Value Watch-CMake

# UTILITY FUNCTIONS

function Add-GhShortcut ($Target, $Path) {
    New-Item -ItemType SymbolicLink -Path $Path -Target $Target
}
Set-Alias -Name shortcut -Value Add-GhShortcut

function Add-Gh7Zip ($Zip) {
    7z a $Zip $args
}
Set-Alias -Name zip -Value Add-Gh7Zip

function Get-ASIOSDK {
    $ASIO_SDK_URL = "https://www.steinberg.net/asiosdk"
    $SDK_DOWNLOAD_FILE = "asiosdk.zip"
    $LIBS_DIR = "libs"
    $SDK_DIRNAME = "asio"
    $SDK_LOCATION = "$LIBS_DIR\$SDK_DIRNAME"

    Write-Output "-- Checking for Steinberg ASIO SDK"
    if (! (Test-Path $SDK_LOCATION)) {
        if (! (Test-Path $SDK_DOWNLOAD_FILE)) {
            Write-Output "-- Downloading $SDK_DOWNLOAD_FILE"
            Invoke-WebRequest -Uri $ASIO_SDK_URL -UseBasicParsing -OutFile $SDK_DOWNLOAD_FILE
        }
        else {
            Write-Output "-- Found $SDK_DOWNLOAD_FILE"
        }
        Write-Output "-- Extracting to $SDK_LOCATION"
        Expand-Archive $SDK_DOWNLOAD_FILE $LIBS_DIR
        Push-Location -Path $LIBS_DIR
    (Get-ChildItem -Filter "$SDK_DIRNAME*")[0] | Rename-Item -NewName { $_.Name -Replace $_.Name, $SDK_DIRNAME }
        Pop-Location
    }
    else {
        Write-Output "-- Steinberg ASIO SDK location: $SDK_LOCATION"
    }
    if ((Test-Path $SDK_DOWNLOAD_FILE)) {
        Remove-Item $SDK_DOWNLOAD_FILE
        Write-Output "-- Cleaning up $SDK_DOWNLOAD_FILE"
    }
    Write-Output "-- The resulting standalone executables are not licensed for distribution"
}
Set-Alias -Name asio -Value Get-ASIOSDK
