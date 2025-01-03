@{
    ModuleVersion = '1.0'

    NestedModules = @(
        './modules/Linters/Helpers/Helpers.psm1'
        './modules/Linters/Linters.psm1'
    )

    FunctionsToExport = @(
        "Test-GitAttributesFile",
        "Test-CSpellConfigurationFile",
        "Test-CodeUsingCSpell",
        "Test-CodeUsingPrettier",
        "Test-CodeUsingPSScriptAnalyzer",
        "Test-CodeUsingClang",
        "Test-CodeUsingAllLinters"
    )
}
