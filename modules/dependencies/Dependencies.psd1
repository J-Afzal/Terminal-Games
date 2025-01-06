@{
    ModuleVersion = "1.0"

    NestedModules = @(
        "./modules/dependencies/Dependencies.psm1"
    )

    FunctionsToExport = @(
        "Install-BuildDependencies",
        "Install-LintingDependencies"
    )
}
