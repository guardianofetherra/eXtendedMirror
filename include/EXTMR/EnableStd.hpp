/******************************************************************************      
 *      Extended Mirror: EnableStd.hpp                                        *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#ifndef EXTMR_ENABLESTD_HPP
#define	EXTMR_ENABLESTD_HPP

EXTMR_ENABLE_TEMPLATE_1(std::allocator)
template<typename T>
EXTMR_BUILD_CLASS(std::allocator<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::char_traits)
template<typename T>
EXTMR_BUILD_CLASS(std::char_traits<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::equal_to)
template<typename T>
EXTMR_BUILD_CLASS(std::equal_to<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::not_equal_to)
template<typename T>
EXTMR_BUILD_CLASS(std::not_equal_to<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::less)
template<typename T>
EXTMR_BUILD_CLASS(std::less<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::less_equal)
template<typename T>
EXTMR_BUILD_CLASS(std::less_equal<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::greater)
template<typename T>
EXTMR_BUILD_CLASS(std::greater<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::greater_equal)
template<typename T>
EXTMR_BUILD_CLASS(std::greater_equal<T>){}


EXTMR_ENABLE_TEMPLATE_2(std::vector)
template<typename T, typename Allocator>
EXTMR_BUILD_CLASS(std::vector<T, Allocator>){}


EXTMR_ENABLE_TEMPLATE_3(std::basic_string)
template<typename CharT, typename Traits, typename Allocator>
EXTMR_BUILD_CLASS(std::basic_string<CharT, Traits, Allocator>){}


EXTMR_ENABLE_TEMPLATE_3(std::set)
template<typename Key, typename Compare, typename Allocator>
EXTMR_BUILD_CLASS(std::set<Key, Compare, Allocator>){}


EXTMR_ENABLE_TEMPLATE_4(std::map)
template<typename Key, typename T, typename Compare, typename Allocator>
EXTMR_BUILD_CLASS(std::map<Key, T, Compare, Allocator>){}
        
#endif	/* EXTMR_ENABLESTD_HPP */

