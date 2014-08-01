/**\file sample_consensus_initial_alignment_prerejective.cpp
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <dynamic_robot_localization/cloud_matchers/feature_matchers/sample_consensus_initial_alignment_prerejective.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace dynamic_robot_localization {

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <imports>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </imports>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// =============================================================================  <public-section>  ============================================================================
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructor>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

template<typename PointT, typename FeatureT>
SampleConsensusInitialAlignmentPrerejective<PointT, FeatureT>::SampleConsensusInitialAlignmentPrerejective() :
	matcher_scia_(new SampleConsensusPrerejective<PointT, PointT, FeatureT>()),
	number_of_samples_(3) {
	CloudMatcher<PointT>::setCloudMatcher(matcher_scia_);
}
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructor>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <SampleConsensusInitialAlignmentPrerejective-functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<typename PointT, typename FeatureT>
void SampleConsensusInitialAlignmentPrerejective<PointT, FeatureT>::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle,
        ros::NodeHandlePtr& private_node_handle, std::string configuration_namespace) {

	double similarity_threshold;
	private_node_handle->param("similarity_threshold", similarity_threshold, 0.8);
	matcher_scia_->setSimilarityThreshold(similarity_threshold);

	double inlier_fraction;
	private_node_handle->param("inlier_fraction", inlier_fraction, 0.25);
	matcher_scia_->setInlierFraction(inlier_fraction);

	private_node_handle->param("number_of_samples", number_of_samples_, 3);
	matcher_scia_->setNumberOfSamples(number_of_samples_);

	int correspondence_randomness;
	private_node_handle->param("correspondence_randomness", correspondence_randomness, 10);
	matcher_scia_->setCorrespondenceRandomness(correspondence_randomness);

	FeatureMatcher<PointT, FeatureT>::setupConfigurationFromParameterServer(node_handle, private_node_handle, configuration_namespace);
}


template<typename PointT, typename FeatureT>
void SampleConsensusInitialAlignmentPrerejective<PointT, FeatureT>::setMatcherReferenceDescriptors(typename pcl::PointCloud<FeatureT>::Ptr& reference_descriptors) {
	matcher_scia_->setTargetFeatures(reference_descriptors);
}


template<typename PointT, typename FeatureT>
void SampleConsensusInitialAlignmentPrerejective<PointT, FeatureT>::setMatcherAmbientDescriptors(typename pcl::PointCloud<FeatureT>::Ptr& ambient_descriptors) {
	matcher_scia_->setSourceFeatures(ambient_descriptors);
	matcher_scia_->setNumberOfSamples(std::min(number_of_samples_, (int)ambient_descriptors->points.size()));
}
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </SampleConsensusInitialAlignmentPrerejective-functions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// =============================================================================  </public-section>  ===========================================================================

// =============================================================================   <protected-section>   =======================================================================
// =============================================================================   </protected-section>  =======================================================================

// =============================================================================   <private-section>   =========================================================================
// =============================================================================   </private-section>  =========================================================================

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <template instantiations>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </template instantiations>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

} /* namespace dynamic_robot_localization */

