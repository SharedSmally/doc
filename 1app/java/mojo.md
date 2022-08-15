# Mojo
## create a Mojo plugin

## Tips
- Get project directory
Add  maven-project dependency:
```
<groupId>org.apache.maven</groupId><artifactId>maven-project</artifactId><scope>provided</scope>
```
Get the project:
```
@Parameter(readonly = true, defaultValue = "${project}")
private MavenProject project;

/**
 * The maven project.
 * 
 * @parameter expression="${project}"
 * @readonly
 */
private MavenProject project;

this.model = project.getModel();
this.build = model.getBuild();
this.finalName = build.getFinalName();
this.targetDir = new File(build.getDirectory());
```
Get the build path
```
/**
 * @parameter expression="${project.build.directory}/${project.build.finalName}"
 * @readonly
 */
private File outputPath;
```

