ruby-coherence
--------------

Ruby Client for Oracle Cohefence

This is beta. At the moment the client doesn't have good tests, docs or setup instructions.

Setup
=====

Download the Oracle Coherence C++ libraries from OTN
untar/unzip to your preferred location

    ruby extconf.rb --with-coherence-libs=/usr/local/coherence/lib --with-coherence-include=/usr/local/coherence/include
    sudo make install

Add a DYLD_LIBRARY_PATH line to your .profile or wherever you set up your env

    export DYLD_LIBRARY_PATH=/usr/local/coherence/lib

Example
=======

    c = Coherence::NamedCache.new("local-foo") # assuming your coherence-cache-config.xml defines a local cache
    c["foo"] = "bar"
    c["foo"] # => "bar"

API
====

* initialize
* put, []=
* putAll
* get, []
* getAll
* size
* clear
* delete
* keys
* values
* each
* has_key?, include?
* has_value?

TODO
====

* CacheInfo
* increment
* decrement
* insert
* add
* addAll
* invalidate ???
* isValid ???
* erase eraseAll
* exists
* find
* getCacheHits() : CacheStatistics , SimpleCacheStatistics
* getHostName() : InetAddress , InetSocketAddress
* getInfo
* removeAll
* lock
* load
* filters or cohql
* POF for Ruby Object, can it be done?
