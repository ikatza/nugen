
set( NURW_LIBS ${ART_FRAMEWORK_SERVICES_REGISTRY}
               ${ART_ROOT_IO_TFILE_SUPPORT} ${ROOT_CORE}
               ${ART_ROOT_IO_TFILESERVICE_SERVICE}
               ${ART_FRAMEWORK_CORE}
               art_Persistency_Common
               ${ART_FRAMEWORK_IO_SOURCES}
               ${ART_ROOT_IO}
               ${ART_ROOT_IO_ROOTINPUT_SOURCE}
               ${ART_FRAMEWORK_PRINCIPAL}
               art_Persistency_Provenance
               art_Utilities
               canvas
               ${MF_MESSAGELOGGER}
               ${MF_UTILITIES}
               ${FHICLCPP}
               cetlib
               cetlib_except
               ${LOG4CPP}
               ${XML2}
               ${PYTHIA6}
               ${LHAPDF}
               ${GENIE_LIB_LIST}
               ${ROOT_BASIC_LIB_LIST}
               ${ROOT_EG}
               ${ROOT_TREEPLAYER}
               ${ROOT_FFTW}
               ${ROOT_REFLEX}
               ${ROOTSYS}/lib/libEGPythia6.so
               ${ROOT_GUI}
           )

art_make_library( SOURCE NuReweight.cxx
                  LIBRARIES nusimdata_SimulationBase
                            nugen_NuReweight
                            ${NURW_LIBS} )

simple_plugin( ReweightAna module nugen_NuReweight_art
                                  nugen_NuReweight
                                  nusimdata_SimulationBase
                                 ${NURW_LIBS} )

install_headers()
install_fhicl()
install_source()
