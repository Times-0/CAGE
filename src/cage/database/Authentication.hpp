#ifndef CAGE_DATABASE_PUBLIC_AUTHENTICATION_H
#define CAGE_DATABASE_PUBLIC_AUTHENTICATION_H


#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace cage {
namespace database {
	namespace Authentication_ {

		struct Id {
			struct _alias_t {
				static constexpr const char _literal[] = R"("id")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T id;
						T &operator()() { return id; }
						const T &operator()() const { return id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
		};

		struct Last_updated {
			struct _alias_t {
				static constexpr const char _literal[] = R"("last_updated")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T last_updated;
						T &operator()() { return last_updated; }
						const T &operator()() const { return last_updated; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::time_point>;
		};

		struct Activated {
			struct _alias_t {
				static constexpr const char _literal[] = R"("activated")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T activated;
						T &operator()() { return activated; }
						const T &operator()() const { return activated; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean>;
		};

		struct Email {
			struct _alias_t {
				static constexpr const char _literal[] = R"("email")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T email;
						T &operator()() { return email; }
						const T &operator()() const { return email; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Hash_md5 {
			struct _alias_t {
				static constexpr const char _literal[] = R"("hash_md5")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T hash_md5;
						T &operator()() { return hash_md5; }
						const T &operator()() const { return hash_md5; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct Hash_bcrypt {
			struct _alias_t {
				static constexpr const char _literal[] = R"("hash_bcrypt")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T hash_bcrypt;
						T &operator()() { return hash_bcrypt; }
						const T &operator()() const { return hash_bcrypt; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};
	} // namespace Authentication_

	struct Authentication : sqlpp::table_t<Authentication,
				Authentication_::Id,
				Authentication_::Last_updated,
				Authentication_::Activated,
				Authentication_::Email,
				Authentication_::Hash_md5,
				Authentication_::Hash_bcrypt> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = R"("public"."Authentication")";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T Authentication;
					T &operator()() { return Authentication; }
					const T &operator()() const { return Authentication; }
				};
		};
	};
} // namespace database
} // namespace cage

#endif
