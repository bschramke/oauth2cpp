// Copyright (c) Glyn Matthews 2012, 2013, 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "network/uri.hpp"
#include "detail/uri_parse_authority.hpp"

namespace network {
uri_builder::uri_builder(const network::uri &base_uri) {
  if (auto scheme = base_uri.scheme()) {
    set_scheme(string_type(std::begin(*scheme), std::end(*scheme)));
  }

  if (auto user_info = base_uri.user_info()) {
    set_user_info(string_type(std::begin(*user_info), std::end(*user_info)));
  }

  if (auto host = base_uri.host()) {
    set_host(string_type(std::begin(*host), std::end(*host)));
  }

  if (auto port = base_uri.port()) {
    set_port(string_type(std::begin(*port), std::end(*port)));
  }

  if (auto path = base_uri.path()) {
    set_path(string_type(std::begin(*path), std::end(*path)));
  }

  if (auto query = base_uri.query()) {
    set_query(string_type(std::begin(*query), std::end(*query)));
  }

  if (auto fragment = base_uri.fragment()) {
    set_fragment(string_type(std::begin(*fragment), std::end(*fragment)));
  }
}

uri_builder::~uri_builder() NETWORK_URI_NOEXCEPT {}

network::uri uri_builder::uri() const { return network::uri(*this); }

void uri_builder::set_scheme(string_type scheme) {
  // validate scheme is valid and normalize
  scheme_ = boost::to_lower_copy(scheme);
}

void uri_builder::set_user_info(string_type user_info) {
  user_info_ = string_type();
  network::uri::encode_user_info(std::begin(user_info), std::end(user_info),
                                 std::back_inserter(*user_info_));
}

uri_builder &uri_builder::clear_user_info() {
  user_info_ = boost::none;
  return *this;
}

void uri_builder::set_host(string_type host) {
  host_ = string_type();
  auto end = network::uri::encode_host(std::begin(host), std::end(host),
                                       std::back_inserter(*host_));
  std::transform(std::begin(*host_), std::end(*host_), std::begin(*host_),
                 [](string_type::value_type c) { return std::tolower(c); });
}

void uri_builder::set_port(string_type port) {
  port_ = string_type();
  network::uri::encode_port(std::begin(port), std::end(port),
                            std::back_inserter(*port_));
}

uri_builder &uri_builder::clear_port() {
  port_ = boost::none;
  return *this;
}

void uri_builder::set_authority(string_type authority) {
  boost::optional<uri::string_type> user_info, host, port;
  detail::parse_authority(std::begin(authority), std::end(authority),
                          user_info, host, port);

  if (user_info) {
    set_user_info(*user_info);
  }

  if (host) {
    set_host(*host);
  }

  if (port) {
    set_port(*port);
  }
}

void uri_builder::set_path(string_type path) {
  path_ = string_type();
  network::uri::encode_path(std::begin(path), std::end(path),
                            std::back_inserter(*path_));
}

uri_builder &uri_builder::clear_path() {
  path_ = boost::none;
  return *this;
}

void uri_builder::set_query(string_type query) {
  query_ = string_type();
  network::uri::encode_query(std::begin(query), std::end(query),
                             std::back_inserter(*query_));
}

uri_builder &uri_builder::clear_query() {
  query_ = boost::none;
  return *this;
}

void uri_builder::set_fragment(string_type fragment) {
  fragment_ = string_type();
  network::uri::encode_fragment(std::begin(fragment), std::end(fragment),
                                std::back_inserter(*fragment_));
}

uri_builder &uri_builder::clear_fragment() {
  fragment_ = boost::none;
  return *this;
}
}  // namespace network
