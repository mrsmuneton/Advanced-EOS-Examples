#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/crypto.h>
#include <string>

using namespace eosio;
using namespace std;

class vectors : contract {

	public:

		explicit vectors(action_name self) : contract(self) {}
		// @abi action
		void signup(const name account);
		// @abi action
		void add(const name account, string name);

	private:
		// @abi table players i64
		struct Profile {
		    name        		account;
		    vector<uint64_t>	items;
		    auto primary_key() const { return account; };
		    EOSLIB_SERIALIZE(Profile, (account)(items));
		};
		// @abi table items i64
		struct Item {
		    uint64_t    		id;
		    string				name;
		    auto primary_key() const { return id; };
		    EOSLIB_SERIALIZE(Item, (id)(name));
		};

		typedef multi_index<N(players), Profile> profile_table;
		typedef multi_index<N(items), Item> dog_table;
		typedef singleton<N(totalItems), uint64_t> total_items;

		/**
		 * @brief Increment Item Counter
		 * @author Mitch Pierias <github.com/MitchPierias>
		 */
		uint64_t incrementTotalItems() {
			// Increment our counter if it exists and return
			uint64_t currentCount = total_items::exists() ? total_items::get() + 1 : 0;
			total_items::set(currentCount);
			return currentCount;
		}
};

EOSIO_ABI(vectors, (signup)(add));
