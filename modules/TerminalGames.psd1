@{
    ModuleVersion = "1.0"

    NestedModules = @(
        "./modules/dependencies/Dependencies.psm1",
        "./modules/linters/Linters.psm1",
        "./modules/linters/helpers/Helpers.psm1"
    )
}
