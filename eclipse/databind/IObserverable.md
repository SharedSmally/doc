# IObserverable

## IObserverable classes Hierarchy 
With IObserverable + Value/List/Set/Map + Viewer/SWT
- IObservable
    - IDecoratingObservable
    - IVetoableValue
    - IObservableValue
    - IObservableCollection (extends java.util.Collection<E>)
        - IObservableList (extends java.util.List<E>)
        - IObservableSet (extends java.util.Set<E>)
        - IObservableMap (extends java.util.Map<E>)



- IObservable
    - IDecoratingObservable
    - IObservableCollection (extends java.util.Collection<E>)
        - IObservableList (extends java.util.List<E>)
            - ISWTObservableList (extends ISWTObservable)
            - IViewerObservableList (extends IViewerObservable)
        - IObservableSet (extends java.util.Set<E>)
            - IViewerObservableSet (extends IViewerObservable)
        - ISWTObservableList (extends IObservableList, ISWTObservable)
        - IViewerObservableList (extends IObservableList, IViewerObservable)
        - IViewerObservableSet (extends IObservableSet, IViewerObservable)
    - IObservableList (extends IObservableCollection, java.util.List<E>)
        - ISWTObservableList (extends ISWTObservable)
        - IViewerObservableList (extends IViewerObservable)
    - IObservableMap (xtends java.util.Map<K,V>)
    - IObservableSet (extends IObservableCollection, java.util.Set<E>)
        - IViewerObservableSet (extends IViewerObservable)
    - IObservableValue
        - ISWTObservableValue (extends ISWTObservable)
        - IVetoableValue
        - IViewerObservableValue (extends IViewerObservable)
    - ISWTObservable
        - ISWTObservableList (extends IObservableList)
        - ISWTObservableValue (extends IObservableValue)
    - ISWTObservableList (extends IObservableList, ISWTObservable)
    - ISWTObservableValue (extends IObservableValue, ISWTObservable)
    - IVetoableValue
    - IViewerObservable
        - IViewerObservableList (extends IObservableList)
        - IViewerObservableSet (extends IObservableSet)
        - IViewerObservableValue (extends IObservableValue)
    - IViewerObservableList (extends IObservableList, IViewerObservable)
    - IViewerObservableSet (extends IObservableSet, IViewerObservable)
    - IViewerObservableValue (extends IObservableValue, IViewerObservable)



- IObservablesListener
    - IChangeListener
    - IDisposeListener
    - IStaleListener



