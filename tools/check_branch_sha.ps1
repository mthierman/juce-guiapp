# Find latest commit of a branch:
$sha = git ls-remote -h https://github.com/juce-framework/JUCE/ develop
$sha = $sha.Trim("refs/head/develop")
$sha = $sha.Trim()
$sha
# $sha | Measure-Object -Character

# Check for nuget version:
$version = nuget search microsoft.web.webview2 -take 1 -verbosity quiet
($version -like "*1.*").Trim("> Microsoft.Web.WebView2 | ")
