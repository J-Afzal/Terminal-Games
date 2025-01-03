@{
    ModuleVersion = '1.0'

    NestedModules = @(
        '.\scripts\Linters.psm1',
        '.\scripts\Dependencies.psm1',
        '.\scripts\Helpers.psm1'
    )

    FunctionsToExport = @(
        "Test-GitAttributesFile",
        "Test-CSpellConfigurationFile",
        "Test-CodeUsingCSpell",
        "Test-CodeUsingPrettier",
        "Test-CodeUsingPSScriptAnalyzer",
        "Test-CodeUsingClang",
        "Test-CodeUsingAllLinters",

        "Install-BuildDependencies",
        "Install-LintingDependencies",

        "Compare-ObjectExact"
    )
}
