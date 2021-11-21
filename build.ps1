$uproject=@"
"D:\Satisfactory Modding/FactoryGame.uproject"
"@
$shp=@"
"C:\Program Files\Unreal Engine - CSS/Engine/Build/BatchFiles/Build.bat" FactoryGame Win64 Shipping -Project=$uproject -WaitMutex -FromMsBuild
"@
$ded=@"
"C:\Program Files\Unreal Engine - CSS/Engine/Build/BatchFiles/Build.bat" FactoryGameEditor Win64 Development -Project=$uproject -WaitMutex -FromMsBuild
"@
iex "& $ded"
iex "& $shp"