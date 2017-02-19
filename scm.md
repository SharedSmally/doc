## SCM Tools Docker

### Repository Server
- [Nexus docker](https://hub.docker.com/r/sonatype/nexus/)
   - Login admin@admin123
   - Repositories: add ->Configuration: ID/Name=cxxReleases/Hosted/Maven2 -> url http://192.168.99.100:32770/nexus/content/repositories/cxxReleases
   - Security: User -> Role

- JFrog

### Build-Server
- Jenkins
   - Manage Jenkins -> Configure System -> Deployment Dashboard: Repositories URI; git/gradle/grails/...
   - Manage Jenkins -> Plugin Management -> Artifact Uploader
   - New Item (Job) -> Freestyle Project (Configure):  SCM; Build:execute make/nexus artifact uploader: nexus URL; Repository(Nexus Repository ID); Artifacts: ArtifactID-version-classifer-type <= file (build file);  Post archive(archive in Jenkins) 

### SVC: [Software Version Control](https://en.wikipedia.org/wiki/Version_control)
- [ git ] (https://git-scm.com/)
- [Mercurial Hg]()
- svn

### [Issue Tracking](https://en.wikipedia.org/wiki/Comparison_of_issue-tracking_systems)
- Apache Bloodhound:
- Bugzilla
- Trac
- Jira

### [Code Review ](https://en.wikipedia.org/wiki/List_of_tools_for_code_review)
- GitLab

### CI Tools
- [Gitlab-CE](https://hub.docker.com/r/gitlab/gitlab-ce/)

Create group, project. Run **git clone http://_host:port_/_group_/_project_.git** to clone the project.
  
### Postgres Database
- [docker](https://hub.docker.com/_/postgres/)
```
User: postgres
Login: # psql -U postgres
```
