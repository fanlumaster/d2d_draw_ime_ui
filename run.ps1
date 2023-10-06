$content = Get-Content -Path "./CMakeLists.txt"
foreach($line in $content)
{
  if ($line.StartsWith("add_executable"))
  {
    $pattern = "\((.*?)\)"
    if ($line -match $pattern)
    {
      $contentInParentheses = $Matches[1]
      $result = -split $contentInParentheses
      $exePath = "./build/DEBUG/" + $result[0] + ".exe"
      Invoke-Expression $exePath
    }
  }
}
