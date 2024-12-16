#include <boost/test/unit_test.hpp>
#include "conway.hpp"

BOOST_AUTO_TEST_CASE( UpdateCubeFacePadding )
{
    conway::cube<conway::a25, conway::md5x5> cube( conway::cube_face_0_before_update,
                                                   conway::blank_face,
                                                   conway::blank_face,
                                                   conway::blank_face,
                                                   conway::blank_face,
                                                   conway::blank_face );
    cube.update_faces();
    BOOST_CHECK( cube.is_equal<1>( conway::board<conway::a25, conway::md5x5>( conway::cube_face_1_after_update ) ) );
    BOOST_CHECK( cube.is_equal<3>( conway::board<conway::a25, conway::md5x5>( conway::cube_face_3_after_update ) ) );
    BOOST_CHECK( cube.is_equal<4>( conway::board<conway::a25, conway::md5x5>( conway::cube_face_4_after_update ) ) );
    BOOST_CHECK( cube.is_equal<5>( conway::board<conway::a25, conway::md5x5>( conway::cube_face_5_after_update ) ) );
}


