add_example( CopyANonCompositeTransform )
add_example( CopyACompositeTransform )

add_example( TranslateImage )
compare_to_baseline(
  EXAMPLE_NAME TranslateImage
  BASELINE_PREFIX OutputBaseline
)

add_example( ApplyAffineTransformFromHomogeneousMatrixAndResample )
compare_to_baseline(
  EXAMPLE_NAME ApplyAffineTransformFromHomogeneousMatrixAndResample
  BASELINE_PREFIX OutputBaseline
)
