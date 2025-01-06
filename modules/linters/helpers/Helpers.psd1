@{
    ModuleVersion = "1.0"

    NestedModules = @(
        "./modules/linters/helpers/Helpers.psm1"
    )

    FunctionsToExport = @(
        "Assert-ExternalCommandError",
        "Get-AllFilePathsToTest",
        "Get-FilteredFilePathsToTest",
        "Compare-ObjectExact"
    )
}