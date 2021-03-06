set(BASELINE ${OTB_DATA_ROOT}/Baseline/Examples/Markov)
set(INPUTDATA ${OTB_DATA_ROOT}/Examples)

otb_add_test(NAME maTeMarkovClassification1ExampleTest COMMAND ${OTB_TEST_DRIVER}
  --compare-image ${EPSILON_8}
    ${BASELINE}/MarkovClassification1.png
    ${TEMP}/MarkovClassification1.png
  Execute $<TARGET_FILE:MarkovClassification1Example>
    ${INPUTDATA}/QB_Suburb.png
    ${TEMP}/MarkovClassification1.png
    1.0
    20
    1.0
    1 #true to use always the same rand() sample, false otherwise
)

otb_add_test(NAME maTeMarkovClassification2ExampleTest COMMAND ${OTB_TEST_DRIVER}
  --compare-image ${EPSILON_8}
    ${BASELINE}/MarkovClassification2.png
    ${TEMP}/MarkovClassification2.png
  Execute $<TARGET_FILE:MarkovClassification2Example>
    ${INPUTDATA}/QB_Suburb.png
    ${TEMP}/MarkovClassification2.png
    1.0
    5
    1 # true to use always the same rand() sample, false otherwise
)

otb_add_test(NAME maTeMarkovClassification3ExampleTest COMMAND ${OTB_TEST_DRIVER}
  --compare-image ${EPSILON_8}
    ${BASELINE}/MarkovClassification3.png
    ${TEMP}/MarkovClassification3.png
  Execute $<TARGET_FILE:MarkovClassification3Example>
    ${INPUTDATA}/QB_Suburb.png
    ${TEMP}/MarkovClassification3.png
    ${TEMP}/MarkovClassification3_1.png
    1.0 20 1.0 1
)

otb_add_test(NAME maTeMarkovRestaurationExampleTest COMMAND ${OTB_TEST_DRIVER}
  --compare-image ${EPSILON_8}
    ${BASELINE}/MarkovRestauration.png
    ${TEMP}/MarkovRestauration.png
  Execute $<TARGET_FILE:MarkovRestaurationExample>
    ${INPUTDATA}/QB_Suburb.png
    ${INPUTDATA}/QB_Suburb.png
    ${TEMP}/MarkovRestauration.png
    10.0
    30.0
    1.
    1 # true to use always the same rand() sample, false otherwise
)


otb_add_test(NAME maTeMarkovRegularizationExampleTest COMMAND ${OTB_TEST_DRIVER}
  --compare-image ${EPSILON_8}
    ${BASELINE}/MarkovRegularization-scaled.png
    ${TEMP}/MarkovRegularization-scaled.png
  Execute $<TARGET_FILE:MarkovRegularizationExample>
    ${INPUTDATA}/ROI_QB_MUL_1_SVN_CLASS_MULTI.png
    ${TEMP}/MarkovRegularization.png
    ${TEMP}/MarkovRegularization-scaled.png
    0.2
    20
    0.0
    1 # true to use always the same rand() sample, false otherwis
)
