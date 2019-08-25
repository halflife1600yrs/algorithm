$root = ".\.exes"

$file1 = ".\test.cpp"
$file2 = ".\undoneproblems\CF976E.cpp"

$filebase1 = (Get-Item $file1).BaseName
$filebase2 = (Get-Item $file2).BaseName

# g++.exe $file1 -o "$root\$filebase1"
g++.exe $file2 -o "$root\$filebase2"

# Get-Content -Path .\.in -Raw | & $root\$filebase1 > .\1.out
Get-Content -Path .\.in -Raw | & $root\$filebase2 > .\2.out

$str1 = Get-Content .\1.out
$str2 = Get-Content .\2.out

Write-Host $filebase1 has $str1.Length lines`n$filebase2 has $str2.Length lines

for($i=0;$i -le $str1.Length -and $i -le $str2.Length;$i++)
{
    if($str1[$i] -ne $str2[$i])
    {
        Write-Host $str1[$i] `t $str2[$i] `t $i
    }
}