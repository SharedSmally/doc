#[Packer] (https://www.packer.io/)

## [Doc](https://www.packer.io/docs/); [github](https://github.com/mitchellh/packer)

## Command:
```
Usage: packer [--version] [--help] <command> [<args>]

Available commands are:
    build       build image(s) from template
    fix         fixes templates from old versions of packer
    inspect     see components of a template
    push        push a template and supporting files to a Packer build service
    validate    check that a template is valid
    version     Prints the Packer version

Usage: packer build [options] TEMPLATE
  Will execute multiple builds in parallel as defined in the template.
  The various artifacts created by the template will be outputted.
  
Options:
  -color=false               Disable color output (on by default)
  -debug                     Debug mode enabled for builds
  -except=foo,bar,baz        Build all builds other than these
  -only=foo,bar,baz          Build only the specified builds
  -force                     Force a build to continue if artifacts exist, deletes existing artifacts
  -machine-readable          Machine-readable output
  -on-error=[cleanup|abort|ask] If the build fails do: clean up (default), abort, or ask
  -parallel=false            Disable parallelization (on by default)
  -var 'key=value'           Variable for templates, can be used multiple times.
  -var-file=path             JSON file containing user variables.
```
