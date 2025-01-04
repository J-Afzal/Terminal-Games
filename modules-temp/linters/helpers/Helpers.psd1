@{
    ModuleVersion = '1.0'

    NestedModules = @(
        './modules/Linters/Helpers/Helpers.psm1'
    )

    FunctionsToExport = @(
        "Compare-ObjectExact"
    )
}