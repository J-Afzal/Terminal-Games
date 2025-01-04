@{
    ModuleVersion = '1.0'

    NestedModules = @(
        './modules/linters/Linters.psm1'
        './modules/linters/helpers/Helpers.psm1'
    )

    FunctionsToExport = @(
        "Test-GitIgnoreFile",
        "Test-GitAttributesFile",
        "Test-CSpellConfigurationFile",
        "Test-PrettierIgnoreFile",
        "Test-CodeUsingCSpell",
        "Test-CodeUsingPrettier",
        "Test-CodeUsingPSScriptAnalyzer",
        "Test-CodeUsingClang",
        "Test-CodeUsingAllLinters"
    )
}
