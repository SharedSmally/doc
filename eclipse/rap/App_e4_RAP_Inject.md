# DI - Dependency Injection
- [Eclipse4/RCP/Dependency Injection](https://wiki.eclipse.org/Eclipse4/RCP/Dependency_Injection)

## Standard Annotations and Classes
- @Inject (javax.inject)
- @Named (javax.inject)
- @Singleton (javax.inject)
- Provider<T> (javax.inject)
- @PostConstruct, @PreDestroy (javax.annotation)

## E4AP-specific Annotations
- @Optional (org.eclipse.e4.core.di.annotations)
- @Active (org.eclipse.e4.core.contexts)
- @Preference (org.eclipse.e4.core.di.extensions)
- @Creatable (org.eclipse.e4.core.di.annotations)
- @CanExecute, @Execute (org.eclipse.e4.core.di.annotations)
- @Focus (org.eclipse.e4.ui.di)
- @AboutToShow, @AboutToHide (org.eclipse.e4.ui.di)
- @GroupUpdates (org.eclipse.e4.core.di.annotations)
- @EventTopic (org.eclipse.e4.core.di.extensions), @UIEventTopic (org.eclipse.e4.ui.di)

