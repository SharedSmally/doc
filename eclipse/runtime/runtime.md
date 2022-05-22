# Eclipse [Platform](http://wiki.eclipse.org/Platform): 
Eclipse Platform defines the set of frameworks and common services that collectively make up infrastructure required to support the use of Eclipse as a component model, as a Rich Client Platform (RCP) and as a comprehensive tool integration platform.

The Eclipse Platform is divided into component areas as follows:
- Platform UI - Platform user interface, runtime, text editor, search and help components 
- SWT - Standard Widget Toolkit 
- Workspace (Team, CVS, Compare, Resources) - Platform resource management
- Debug - Generic execution debug framework
- Releng - Release Engineering

Document:
- Help: https://help.eclipse.org/latest/index.jsp
- Maven Web Site
  - Eclipse: https://mvnrepository.com/artifact/org.eclipse
    - Core: https://mvnrepository.com/artifact/org.eclipse.core
    - Platform: https://mvnrepository.com/artifact/org.eclipse.platform
- OSGi: compileOnly 'org.eclipse:osgi:3.10.0-v20140606-1445'
- Runtime: org.eclipse.platform:org.eclipse.core.runtime:3.24.100 (OSGi + equinox.*)
- Platform: org.eclipse.platform:org.eclipse.platform:4.23.0 (Runtime + org.eclipse.ui)
- SDK: org.eclipse.platform:org.eclipse.sdk:4.23.0  (Platform + UIs)

## Platforms / SDK
- linux: gtk.x86_64
- windows: win32.x86_64
- macosx.cocoa: x86_64 and aarch64
SWT supports more: hp, ibm, solaris, aix,...

## Components: org.eclipse.platform 
- runtime:  
  - core: org.eclipse.core.runtime
  - expression: org.eclipse.core.expressions
  - jobs: org.eclipse.core.jobs
  - commands: org.eclipse.core.commands
  - contenttype: org.eclipse.core.contenttype
  - variables: org.eclipse.core.variables
  - external tools: org.eclipse.core.externaltools
- databinding
  - core: org.eclipse.core.databinding
  - observables: org.eclipse.core.databinding.observable
  - properties: org.eclipse.core.databinding.property
  - javabeans: org.eclipse.core.databinding.beans
  
- compare: 
   - compare: org.eclipse.compare
   - core: org.eclipse.compare.core
- commands
- resources: org.eclipse.core.resources
- misc
  - net:  org.eclipse.core.net
  - proxy for linux: org.eclipse.core.net.linux
  - ant build tool: org.eclipse.ant.core
  - ant launch: org.eclipse.ant.launching
  - ant ui: org.eclipse.ant.ui
  - scheme: org.eclipse.urischeme
  - update: org.eclipse.update.configurator
  - tips:  org.eclipse.tips.core
  - tips ui: org.eclipse.tips.ui
  - tips json: org.eclipse.tips.json
- osgi: 
  - core: org.eclipse.osgi
  - services: org.eclipse.osgi.services
  - compatibility: org.eclipse.osgi.compatibility.state
  - util: org.eclipse.osgi.util
- cvs client:
  - cvs: org.eclipse.cvs
- filesystem: 
  - filesystem: org.eclipse.core.filesystem
  - filebuffers: org.eclipse.core.filebuffers
- help
  - core: org.eclipse.help
  - base: org.eclipse.help.base
  - ui: org.eclipse.help.ui
- search
  - core: org.eclipse.search
- update
  - core: org.eclipse.update.core
- team
  - core: org.eclipse.team.core
  - ui: org.eclipse.team.ui
  - cvs: org.eclipse.team.cvs.core
  - cvs ui: org.eclipse.team.cvs.ui
- jsch
  - core: org.eclipse.jsch.core
  - ui: org.eclipse.jsch.ui
- text: org.eclipse.text
- debug
  - core:  org.eclipse.debug.core
  - ui:  org.eclipse.debug.ui

## runtime
- org.eclipse.core.runtime
- org.eclipse.core.runtime.adaptor
- corg.eclipse.core.runtime.content
- org.eclipse.core.runtime.dynamichelpers
- org.eclipse.core.runtime.spi
- org.eclipse.core.runtime.jobs
- org.eclipse.core.runtime.preferences

## databinding
- org.eclipse.core.databinding
- org.eclipse.core.databinding.beans
- org.eclipse.core.databinding.conversion
- org.eclipse.core.databinding.observable
- org.eclipse.core.databinding.observable.list
- org.eclipse.core.databinding.observable.map
- org.eclipse.core.databinding.observable.masterdetail
- org.eclipse.core.databinding.observable.set
- org.eclipse.core.databinding.observable.value
- org.eclipse.core.databinding.property
- org.eclipse.core.databinding.property.list
- org.eclipse.core.databinding.property.map
- org.eclipse.core.databinding.property.set
- org.eclipse.core.databinding.property.value
- org.eclipse.core.databinding.util
- org.eclipse.core.databinding.validation

## compare
- org.eclipse.compare
- org.eclipse.compare.contentmergeviewer
- org.eclipse.compare.patch
- org.eclipse.compare.rangedifferencer
- org.eclipse.compare.structuremergeviewer

## commands
- org.eclipse.core.commands
- org.eclipse.core.commands.common
- org.eclipse.core.commands.contexts
- org.eclipse.core.commands.operations
- org.eclipse.core.commands.util

## resources
- org.eclipse.core.resources
- org.eclipse.core.resources.filtermatchers
- org.eclipse.core.resources.refresh
- org.eclipse.core.resources.mapping
- org.eclipse.core.resources.team
- org.eclipse.core.resources.variableresolvers

## filesystem
- org.eclipse.core.filebuffers
- org.eclipse.core.filebuffers.manipulation
- org.eclipse.core.filesystem
- org.eclipse.core.filesystem.provider

## misc
- org.eclipse.ant.core
- org.eclipse.core.expressions
- org.eclipse.core.net.proxy
- org.eclipse.core.variables

## osgi
- org.eclipse.osgi.framework.console
- org.eclipse.osgi.framework.eventmgr
- org.eclipse.osgi.framework.log
- org.eclipse.osgi.launch
- org.eclipse.osgi.service.datalocation
- org.eclipse.osgi.service.debug
- org.eclipse.osgi.service.environment
- org.eclipse.osgi.service.localization
- org.eclipse.osgi.service.resolver
- org.eclipse.osgi.service.runnable
- org.eclipse.osgi.service.security
- org.eclipse.osgi.signedcontent
- org.eclipse.osgi.storagemanager
- org.eclipse.osgi.util

## help
- org.eclipse.help
- org.eclipse.help.base
- org.eclipse.help.browser
- org.eclipse.help.search
- org.eclipse.help.server
- org.eclipse.help.standalone
- org.eclipse.help.ui
- org.eclipse.help.ui.browser
- org.eclipse.help.webapp

## search
- org.eclipse.search.core.text
- org.eclipse.search.ui
- org.eclipse.search.ui.actions
- org.eclipse.search.ui.text

## team
- org.eclipse.team.core
- org.eclipse.team.core.diff
- org.eclipse.team.core.diff.provider
- org.eclipse.team.core.history
- org.eclipse.team.core.history.provider
- org.eclipse.team.core.mapping
- org.eclipse.team.core.mapping.provider
- org.eclipse.team.core.subscribers
- org.eclipse.team.core.synchronize
- org.eclipse.team.core.variants
- org.eclipse.team.ui
- org.eclipse.team.ui.history
- org.eclipse.team.ui.mapping
- org.eclipse.team.ui.synchronize

## jsch
- org.eclipse.jsch.core
- org.eclipse.jsch.ui

## text
- org.eclipse.text.edits
- org.eclipse.text.undo

## debug
- org.eclipse.debug.core
- org.eclipse.debug.core.commands
- org.eclipse.debug.core.model
- org.eclipse.debug.core.sourcelookup
- org.eclipse.debug.core.sourcelookup.containers
- org.eclipse.debug.ui
- org.eclipse.debug.ui.actions
- org.eclipse.debug.ui.console
- org.eclipse.debug.ui.contexts
- org.eclipse.debug.ui.memory
- org.eclipse.debug.ui.sourcelookup
- org.eclipse.debug.ui.stringsubstitution
