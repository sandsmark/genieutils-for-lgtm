/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  Armin Preiml
    Copyright (C) 2015 - 2016  Mikko "Tapsa" P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genie/resource/BlendomaticFile.h"

#include <stdexcept>
#include <chrono>
#include <cmath>

#include "genie/resource/BlendomaticFile.h"

namespace genie
{

Logger& BlendomaticFile::log = Logger::getLogger("genie.BlendomaticFile");

//------------------------------------------------------------------------------
BlendomaticFile::BlendomaticFile() : IFile()
{
}

//------------------------------------------------------------------------------
BlendomaticFile::~BlendomaticFile()
{
}

//------------------------------------------------------------------------------
void BlendomaticFile::serializeObject(void)
{
    serialize(modeCount_);
    serialize(tileCount_);

    for (uint32_t i=0; i < modeCount_; i++) {
        log.debug("reading mode %d", i);

        BlendModePtr mode;
        if (isOperation(OP_READ)) {
            mode = std::make_unique<BlendMode>();
            modes_.push_back(mode);
        } else {
            mode = modes_[i];
        }

        // number of pixels
        serialize(mode->pixelCount);
        if (mode->pixelCount > 3000) {
            std::cerr << "invalid pixel count " << mode->pixelCount << std::endl;
            exit(0);
        }

        // TODO:
        // we should check these and skip the alphaValues reading in case any tiles don't have alpha
        serialize(mode->tileHasAlpha, tileCount_);

        serialize(mode->alphaBitmap, mode->pixelCount);

        // alpha values from 0-128
        serialize(mode->alphaValues, tileCount_, mode->pixelCount);
    }
}

//------------------------------------------------------------------------------
void BlendomaticFile::unload(void)
{
    modes_.clear();
    modeCount_ = 0;
    tileCount_ = 0;
}

void BlendomaticFile::setBlendMode(uint32_t number, BlendModePtr mode)
{
    if (number >= modes_.size()) {
        modes_.resize(number + 1);
    }
    modes_[number] = mode;
}

BlendModePtr BlendomaticFile::getBlendMode(uint32_t id)
{
    if (id > modes_.size()) {
        log.error("Invalid blendomatic id %d", id);
        return nullptr;
    }

    return modes_[id];
}


}