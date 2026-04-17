include("/home/lxs/DVD-simulator/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/DVD-simulator-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/lxs/DVD-simulator/build/Desktop-Debug/DVD-simulator"
    GENERATE_QT_CONF
)
