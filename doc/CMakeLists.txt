# This CMake file will add doc target for convenient documentation generation.
#
# Additional features are supported:
#   * dot = for automatically generated UML diagrams (class, include, caller, call, collaboration)
#   * PlantUML = for easy generation of custom diagrams

# Helper functions
macro(path_linux_to_win MsysPath ResultingPath)
  string(REGEX REPLACE "^/([a-zA-Z])/" "\\1:/" ${ResultingPath} "${MsysPath}")
endmacro()
macro(path_win_to_linux MsysPath ResultingPath)
  string(REGEX REPLACE "^([a-zA-Z]):/" "/\\1/" ${ResultingPath} "${MsysPath}")
endmacro()


