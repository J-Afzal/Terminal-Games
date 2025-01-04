@{
    ModuleVersion = '1.0'

    NestedModules = @(
        './modules/linters/helpers/Helpers.psm1'
    )

    FunctionsToExport = @(
        "Compare-ObjectExact"
    )
}