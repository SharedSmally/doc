# IObserverable

## IObserverable classes Hierarchy 
With IObserverable + Value/List/Set/Map + Viewer/SWT
- IObservable
    - IDecoratingObservable
    - IVetoableValue: 
    - IObservableValue: get/setValue
    - IObservableCollection (extends java.util.Collection<E>)
        - IObservableList (extends java.util.List<E>)
        - IObservableSet (extends java.util.Set<E>)
        - IObservableMap (extends java.util.Map<E>)

### IObserverable 
Extending the corresponding classes or ChangeSupport to handle the listeners management.
    
| Method | Description|
|--------|-------------|    
|void 	remove/addChangeListener(IChangeListener listener) 	 | Adds the given change listener to the list of change listeners.
|void 	remove/addDisposeListener(IDisposeListener listener) 	|Adds the given dispose listener to the list of dispose listeners.|
|void 	remove/addStaleListener(IStaleListener listener) 	|Adds the given stale listener to the list of stale listeners.|
|void 	dispose() 	|Disposes of this observable object, removing all listeners registered with this object, and all listeners this object might have registered on other objects.|
|Realm 	getRealm() 	|Returns the realm for this observable.|
|boolean 	isDisposed() 	|Returns whether the observable has been disposed|
|boolean 	isStale() 	|Returns whether the state of this observable is stale and is expected to change soon.|
  
### IVetoableValue<T>     
| Method | Description|
|--------|-------------|    
|void 	remove/addValueChangingListener​(IValueChangingListener<T> listener)||
    
### ISWTObservable  
| Method | Description|
|--------|-------------|    
|Widget 	getWidget() 	|Returns the widget of this observable    |
    
### IDecoratingObservable    
| Method | Description|
|--------|-------------|    
|IObservable 	getDecorated()||
    
### IObservableValue<T>    
| Method | Description|
|--------|-------------|    
|void 	remove/addValueChangeListener(IValueChangeListener<? super T> listener) 	 
|T 	getValue() 	|Returns the value.|
|void 	setValue(T value) 	|Sets the value.|
|Object 	getValueType() 	|The value type of this observable value, or null if this observable value is untyped.|

### IObservableSet<T>    
| Method | Description|
|--------|-------------|    
|abstract Set<E> 	getAdditions() 	 ||
|abstract Set<E> 	getRemovals()    ||
    
### Interface IDiff
    All Known Implementing Classes: ListDiff, MapDiff, SetDiff, ValueDiff 

### Class ValueDiff<T>
| Method | Description|
|--------|-------------|  
|abstract T 	getNewValue() 	 ||
|abstract T 	getOldValue()    ||

##  classes Hierarchy 
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



