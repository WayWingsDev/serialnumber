@"c:\program files (x86)\national instruments\cvi2013\bin\cvilink.exe" -cmd:link_options.txt -flags:16 -expiry:1433368799 > Link.out 2>&1
@if errorlevel 1 goto err
@echo Link success
@echo Link complete
@exit 0
:err
@echo Link complete
@echo Link failed
@exit 1
