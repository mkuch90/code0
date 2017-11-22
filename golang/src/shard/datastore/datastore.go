package datastore

import (
	"sync"
)

type Datastore struct {
	store       map[string]string
	global_lock sync.Mutex
}

func NewDatastore() Datastore {
	datastore := new(Datastore)
	datastore.store = make(map[string]string)
	return *datastore
}

func (store Datastore) Insert(key string, value string) {
	store.global_lock.Lock()
	store.store[key] = value
	store.global_lock.Unlock()

}

func (store Datastore) Retrieve(key string) string {
	store.global_lock.Lock()
	val := store.store[key]
	store.global_lock.Unlock()
	return val
}
