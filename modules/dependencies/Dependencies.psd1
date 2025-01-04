@{
    ModuleVersion = '1.0'

    NestedModules = @(
        './modules/Dependencies/Dependencies.psm1'
    )

    FunctionsToExport = @(
        "Install-BuildDependencies",
        "Install-LintingDependencies"
    )
}
