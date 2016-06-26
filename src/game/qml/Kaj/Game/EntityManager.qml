import QtQuick 2.0

/*!
 * \addtogroup Game
 */
QtObject {
    id: manager

    /*!
	 * The parent of EntityManager that should Entities add to it
	 */ 
    property var parent
    
    /*! \cond PRIVATE */
    property var __pool: []

    function _createFromPool(type, variant){
        var i
        for(i = 0; i < __pool.length; i++)
            if(__pool[i].entityType === type){
                var ret = __pool[i]
                __pool.splice(ret, 1)
                return ret;
            }

        return false
    }
    /*! \endcond */

    function clearPool(){
        __pool = []
    }

    function createPooled(url, count, opts){
        var i
        for(i = 0; i < count; i++){
            var item
            var component = Qt.createComponent(url);

            if (component.status === Component.Error) {
                // Error Handling
                console.log("Error loading component:", component.errorString())
                return false
            }

            if(opts === undefined || opts === false)
                item = component.createObject(parent);
            else
                item = component.createObject(parent, opts);

            item.manager = manager
            item.onRemove.connect(remove)
            item.visible = false

            __pool.push(item)
        }
    }

    function create(url, opts, type, variant){
        var pooled = _createFromPool(type, variant)

        if(pooled !== false)
            return pooled

        var item
        var component = Qt.createComponent(url);

        if (component.status === Component.Error) {
            // Error Handling
            console.log("Error loading component:", component.errorString())
            return false
        }

        if(opts === undefined || opts === false)
            item = component.createObject(parent);
        else
            item = component.createObject(parent, opts);

        item.manager = manager
        item.onRemove.connect(remove)

        return item
    }

    function remove(item){
        item.visible = false
        __pool.push(item)
    }

}

