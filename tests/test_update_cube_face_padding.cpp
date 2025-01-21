#include <boost/test/unit_test.hpp>
#include "conway.hpp"

using namespace conway;

BOOST_AUTO_TEST_CASE( UpdateCubeFacePadding )
{
    cube<a25, md5x5> cube( cube_face_0_before_update,
                           blank_face,
                           blank_face,
                           blank_face,
                           blank_face,
                           blank_face );
    cube.update_faces();
    BOOST_CHECK( cube.is_equal<1>( board<a25, md5x5>( cube_face_1_after_update ) ) );
    BOOST_CHECK( cube.is_equal<3>( board<a25, md5x5>( cube_face_3_after_update ) ) );
    BOOST_CHECK( cube.is_equal<4>( board<a25, md5x5>( cube_face_4_after_update ) ) );
    BOOST_CHECK( cube.is_equal<5>( board<a25, md5x5>( cube_face_5_after_update ) ) );
}


