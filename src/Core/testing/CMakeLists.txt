
# TESTS
set( TESTS
        SmartVectorTest
        VectorTest
        ObjectFlagsTest
        ObjectParametersTest
        ObjectCopyTest
        StaticInterfaceTest
        CommaInitTest
        DebugTTreeDumpTest
        BoostTest
        BoostAccumulatorTest
        PropertiesTest
        SignalTest
        SerializeTest
        SerializeDreadDiamondTest
        DreadDiamondParameters
        ObjectPropableTest
        UuidTest
        TypeIntrospectionTraversal
        OptionsTest
)

set(LIBRARIES
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${ROOT_LIBRARIES}
)
uLib_add_tests(${uLib-module})
