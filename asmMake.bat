@echo off

    if exist "a.obj" del "a.obj"
    if exist "a.exe" del "a.exe"

    \masm32\bin\ml /c /Zd /coff "a.asm"
    if errorlevel 1 goto errasm

    \masm32\bin\Link /SUBSYSTEM:CONSOLE "a.obj"
    if errorlevel 1 goto errlink
    dir "a.*"
    goto TheEnd

  :errlink
    echo _
    echo Link error
    goto TheEnd

  :errasm
    echo _
    echo Assembly Error
    goto TheEnd
    
  :TheEnd
