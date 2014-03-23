/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_drawinglayer.hxx"

#include <drawinglayer/primitive2d/cropprimitive2d.hxx>
#include <drawinglayer/primitive2d/drawinglayer_primitivetypes2d.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>
#include <basegfx/matrix/b2dhommatrixtools.hxx>
#include <drawinglayer/primitive2d/transformprimitive2d.hxx>
#include <basegfx/polygon/b2dpolygon.hxx>
#include <basegfx/polygon/b2dpolygontools.hxx>
#include <drawinglayer/primitive2d/maskprimitive2d.hxx>

//////////////////////////////////////////////////////////////////////////////

using namespace com::sun::star;

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
    namespace primitive2d
    {
        CropPrimitive2D::CropPrimitive2D(
            const Primitive2DSequence& rChildren,
            const basegfx::B2DHomMatrix& rTransformation, 
            double fCropLeft,
            double fCropTop,
            double fCropRight,
            double fCropBottom)
        :   GroupPrimitive2D(rChildren),
            maTransformation(rTransformation),
            mfCropLeft(fCropLeft),
            mfCropTop(fCropTop),
            mfCropRight(fCropRight),
            mfCropBottom(fCropBottom)
        {
        }

        Primitive2DSequence CropPrimitive2D::get2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
        {
            Primitive2DSequence xRetval;

            if(getChildren().hasElements())
            {
                // get original object scale in unit coordinates (no mirroring)
                const basegfx::B2DVector aObjectScale(basegfx::absolute(getTransformation() * basegfx::B2DVector(1.0, 1.0)));

                // we handle cropping, so when no width or no height, content will be empty,
                // so only do something when we have a width and a height
                if(!aObjectScale.equalZero())
                {
                    // calculate crop distances in unit coordinates. They are already combined with CropScaleFactor, thus
                    // are relative only to object scale
                    const double fBackScaleX(basegfx::fTools::equalZero(aObjectScale.getX()) ? 1.0 : 1.0 / fabs(aObjectScale.getX()));
                    const double fBackScaleY(basegfx::fTools::equalZero(aObjectScale.getY()) ? 1.0 : 1.0 / fabs(aObjectScale.getY()));
                    const double fLeft(getCropLeft() * fBackScaleX);
                    const double fTop(getCropTop() * fBackScaleY);
                    const double fRight(getCropRight() * fBackScaleX);
                    const double fBottom(getCropBottom() * fBackScaleY);

                    // calc new unit range for comparisons; the original range is the unit range
                    const basegfx::B2DRange aUnitRange(0.0, 0.0, 1.0, 1.0);
                    const basegfx::B2DRange aNewRange(
                        -fLeft,
                        -fTop,
                        1.0 + fRight,
                        1.0 + fBottom);

                    // if we have no overlap the crop has removed everything, so we do only
                    // have to create content if this is not the case
                    if(aNewRange.overlaps(aUnitRange))
                    {
                        // create new transform; first take out old transform to get
                        // to unit coordinates by inverting. Inverting should be flawless
                        // since we already cheched that object size is not zero in X or Y
                        basegfx::B2DHomMatrix aNewTransform(getTransformation());

                        aNewTransform.invert();

                        // apply crop enlargement in unit coordinates
                        aNewTransform = basegfx::tools::createScaleTranslateB2DHomMatrix(
                            aNewRange.getRange(),
                            aNewRange.getMinimum()) * aNewTransform;

                        // apply original transformation. Since we have manipulated the crop
                        // in unit coordinates we do not need to care about mirroring or
                        // a corrected point for eventual shear or rotation, this all comes for
                        // free
                        aNewTransform = getTransformation() * aNewTransform;

                        // prepare TransformPrimitive2D with xPrimitive
                        const Primitive2DReference xTransformPrimitive(
                            new TransformPrimitive2D(
                                aNewTransform, 
                                getChildren()));

                        if(aUnitRange.isInside(aNewRange))
                        {
                            // the new range is completely inside the old range (unit range),
                            // so no masking is needed
                            xRetval = Primitive2DSequence(&xTransformPrimitive, 1);
                        }
                        else
                        {
                            // mask with original object's bounds
                            basegfx::B2DPolyPolygon aMaskPolyPolygon(basegfx::tools::createUnitPolygon());
                            aMaskPolyPolygon.transform(getTransformation());

                            // create maskPrimitive with aMaskPolyPolygon and aMaskContentVector
                            const Primitive2DReference xMask(
                                new MaskPrimitive2D(
                                    aMaskPolyPolygon, 
                                    Primitive2DSequence(&xTransformPrimitive, 1)));

                            xRetval = Primitive2DSequence(&xMask, 1);
                        }
                    }
                }
            }

            return xRetval;
        }

        // provide unique ID
        ImplPrimitrive2DIDBlock(CropPrimitive2D, PRIMITIVE2D_ID_CROPPRIMITIVE2D)

    } // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////
// eof